#include "pp_extram_quadspi_ft8xx.h"
//#include "stdio.h"
#include <string.h>
#include "platform_io_signals.h"
#include "delay.h"

void setSpiDataModeExtRAMft8XX(PExtRamData *data, QuadSpiDataMode dataMode){

	data->spiDataMode=dataMode;
	
};

void resetExtRAMft8XX(PExtRamData *data){
	
	data->spiDataMode=SINGLE_LINE;
	data->focusAdress=data->firstAdress;
	
	PIN_CLR(PORT_TFT, PIN_TFT_PD);
	delay_ms(20);
	PIN_SET(PORT_TFT, PIN_TFT_PD);
	delay_ms(20);

}

bool openExtRAMft8XX(PExtRamData *data, OpenMode mode){
	
	data->openMode=mode;
	
	OCTOSPI1->CR |=OCTOSPI_CR_EN;
	data->isOpen=true;
	return true;
}

bool closeExtRAMft8XX(PExtRamData *data){
	
	OCTOSPI1->CR&=~OCTOSPI_CR_EN;
	data->isOpen=false;
	return true;
}



void portListenExtRAMft8XX(PExtRamData* data){
	

	
	 if((OCTOSPI1->SR & OCTOSPI_SR_FTF) && (OCTOSPI1->CR & OCTOSPI_CR_FTIE)){
    if((OCTOSPI1->CR & OCTOSPI_CR_FMODE)==0){	
			if(data->sendSingleBytes){
				sendWord8FromSendQueueExtRAMft8XX(data);
			}else{
				sendWord32FromSendQueueExtRAMft8XX(data);
			}
    }else if((OCTOSPI1->CR & OCTOSPI_CR_FMODE)==OCTOSPI_CR_FMODE_0){
				receiveAndWriteToReceiveQueueExtRAMft8XX(data);
    }   
  }
	 
	  /* QSPI Transfer Complete interrupt occurred -------------------------------*/
   if((OCTOSPI1->SR & OCTOSPI_SR_TCF) && (OCTOSPI1->CR & OCTOSPI_CR_TCIE)){
    OCTOSPI1->FCR|=OCTOSPI_FCR_CTCF; //clear interrupt
    
    /* Disable the QSPI FIFO Threshold, Transfer Error and Transfer complete Interrupts */
		OCTOSPI1->CR &=~OCTOSPI_CR_TEIE;	//transfer complete interupt disable
		OCTOSPI1->CR &=~OCTOSPI_CR_TCIE;	//transfer error interupt disable
		OCTOSPI1->CR &=~OCTOSPI_CR_FTIE;	//treshold interupt disable;	
    
     OCTOSPI1->CR |= OCTOSPI_CR_ABORT;
		 data->rdWrInProgress=false;

  }  
  /* QSPI Status Match interrupt occurred ------------------------------------*/
  if((OCTOSPI1->SR & OCTOSPI_SR_SMF) && (OCTOSPI1->CR & OCTOSPI_CR_SMIE)){
    /* Clear flag */
    OCTOSPI1->FCR|=OCTOSPI_FCR_CSMF; //clear interrupt
    
    /* Disable the QSPI FIFO Threshold, Transfer Error and Status Match Interrupts */
		OCTOSPI1->CR &=~OCTOSPI_CR_TEIE;	//transfer complete interupt disable
		OCTOSPI1->CR &=~OCTOSPI_CR_SMIE;	//status match interupt disable
		OCTOSPI1->CR &=~OCTOSPI_CR_FTIE;	//treshold interupt disable;	
		data->rdWrInProgress=false;

  }  

  /* QSPI Transfer Error interrupt occurred ----------------------------------*/
  if((OCTOSPI1->SR & OCTOSPI_SR_TEF) && (OCTOSPI1->CR & OCTOSPI_CR_TEIE)){
		OCTOSPI1->FCR|=OCTOSPI_FCR_CTEF; //clear interrupt
    
    /* Disable all the QSPI Interrupts */
		OCTOSPI1->CR &=~OCTOSPI_CR_TEIE;	//transfer complete interupt disable
		OCTOSPI1->CR &=~OCTOSPI_CR_TCIE;	//transfer error interupt disable
		OCTOSPI1->CR &=~OCTOSPI_CR_FTIE;	//treshold interupt disable;	
		OCTOSPI1->CR &=~OCTOSPI_CR_SMIE;	//status match interupt disable;	
		data->rdWrInProgress=false;

  }
  
  /* QSPI Timeout interrupt occurred -----------------------------------------*/
  if((OCTOSPI1->SR & OCTOSPI_SR_TOF) && (OCTOSPI1->CR & OCTOSPI_CR_TOIE)){
		OCTOSPI1->FCR|=OCTOSPI_FCR_TOF; //clear interrupt
		data->rdWrInProgress=false;

  }
}

void sendWord8FromSendQueueExtRAMft8XX(PExtRamData* data){
	uint32_t octospi1base = 0;

	octospi1base = (uint32_t)OCTOSPI1; 
	octospi1base += 0x50;
	
	int sign=0;
	bool status=data->sendQueue->dequeue(&data->sendQueue->data, &sign, 0);
	
	if(status){
		*(__IO uint8_t *) octospi1base=(uint8_t)sign;
	}else{
		OCTOSPI1->CR &=~OCTOSPI_CR_FTIE;	
		data->rdWrInProgress=false;
	}
 }


void sendWord32FromSendQueueExtRAMft8XX(PExtRamData* data){

	
	int word=0;
	bool status=data->sendQueue->dequeue(&data->sendQueue->data, &word, 0);
	
	if(status){
		OCTOSPI1->DR=word;
	}else{
		OCTOSPI1->CR &=~OCTOSPI_CR_FTIE;	
		data->rdWrInProgress=false;
	}
 }

void receiveAndWriteToReceiveQueueExtRAMft8XX(PExtRamData* data){

	data->nbrOfDataToRead--;
	if(data->nbrOfDataToRead>=0){
	
		unsigned int receiveData=OCTOSPI1->DR;
		if(data->openMode==ReadOnly || data->openMode==ReadWrite){
			data->receiveQueue->enqueue(&data->receiveQueue->data, receiveData, 0);
		}
	}
	
	if(data->nbrOfDataToRead<=0){
		OCTOSPI1->CR &=~OCTOSPI_CR_FTIE;	
		data->rdWrInProgress=false;
	}
	
}

int readExtRAMft8XX(PExtRamData *data){

	int dataToReceive[1]={0};
	readTabExtRAMft8XX(data, dataToReceive, 1);
	
	return dataToReceive[0];
	
}


void readTabExtRAMft8XX(PExtRamData *data, int *dataToReceive, int dataSize){

	if(dataSize>0){
		while((OCTOSPI1->SR & OCTOSPI_SR_BUSY) || data->rdWrInProgress);
		
		data->rdWrInProgress=true;
		data->sendSingleBytes=false;
		OCTOSPI1->CR=(OCTOSPI1->CR & ~OCTOSPI_CR_FTHRES) | (3<<OCTOSPI_CR_FTHRES_Pos);

		
		data->nbrOfDataToRead=dataSize;
		data->nbrOfDataToTransfer=dataSize;
		
		
		OCTOSPI1->DLR = sizeof(int)*dataSize-1;
		OCTOSPI1->CR = (OCTOSPI1->CR & ~OCTOSPI_CR_FMODE) | OCTOSPI_CR_FMODE_0;			//Functional mode: Indirect-read mode
		
		if(data->spiDataMode==QUAD_LINE){
			OCTOSPI1->CCR = (OCTOSPI1->CCR & ~OCTOSPI_CCR_ADMODE) | OCTOSPI_CCR_ADMODE_1 | OCTOSPI_CCR_ADMODE_0;		//Address mode: Address on four lines
			OCTOSPI1->CCR = (OCTOSPI1->CCR & ~OCTOSPI_CCR_ADSIZE) | OCTOSPI_CCR_ADSIZE_1;  	//Address size: 24-bit address
			OCTOSPI1->TCR = (OCTOSPI1->TCR & ~OCTOSPI_TCR_DCYC) | (2<<OCTOSPI_TCR_DCYC_Pos);	
			OCTOSPI1->CCR = (OCTOSPI1->CCR & ~OCTOSPI_CCR_DMODE) | OCTOSPI_CCR_DMODE_1 | OCTOSPI_CCR_DMODE_0;		//Data mode: Data on four lines
			OCTOSPI1->AR = (data->focusAdress & 0x3FFFFF);			
		}else{
			OCTOSPI1->CCR = (OCTOSPI1->CCR & ~OCTOSPI_CCR_ADMODE) | OCTOSPI_CCR_ADMODE_0;		//Address mode: Address on a single line
			OCTOSPI1->CCR = (OCTOSPI1->CCR & ~OCTOSPI_CCR_ADSIZE) | OCTOSPI_CCR_ADSIZE_1 | OCTOSPI_CCR_ADSIZE_0;	//Address size: 32-bit address
			OCTOSPI1->TCR = (OCTOSPI1->TCR & ~OCTOSPI_TCR_DCYC);
			OCTOSPI1->CCR = (OCTOSPI1->CCR & ~OCTOSPI_CCR_DMODE) | OCTOSPI_CCR_DMODE_0;			//Data mode: Data on a signle line
			OCTOSPI1->AR = (data->focusAdress & 0x3FFFFF)<<8;//between the address and the dummy byte a logical 1 appears for one clock cycle; to avoid this I enter this one dummy byte into the address
		}
		

		OCTOSPI1->CR |=OCTOSPI_CR_FTIE;		//treshold interupt enable
		OCTOSPI1->CR |=OCTOSPI_CR_TCIE;		//transfer complete interupt enable
		OCTOSPI1->CR |=OCTOSPI_CR_TEIE;	//transfer error interupt enable


		data->focusAdress+=sizeof(int)*dataSize;
		
		int timeout=100;
		while(1){
			waitForReadyReadExtRAMft8XX(data);
			if(data->getDataFlag){
				memcpy(dataToReceive, data->receiveData, sizeof(int)*dataSize);
				memset(data->receiveData, 0, sizeof(data->receiveData));
				data->nbrOfDataToTransfer=0;
				data->getDataFlag=false;
				break;
			}
			
			timeout--;
			if(timeout<=0){
				memset(dataToReceive, -1, sizeof(int)*dataSize);
				data->nbrOfDataToTransfer=0;
				
				OCTOSPI1->CR &=~OCTOSPI_CR_FTIE;	
				OCTOSPI1->CR |= OCTOSPI_CR_ABORT;
				data->rdWrInProgress=false;
				break;
			}
			
		}
		
	}
}

void writeHostCommExtRAMft8XX(PExtRamData *data, unsigned int command, unsigned int param){
	
		while((OCTOSPI1->SR & OCTOSPI_SR_BUSY) || data->rdWrInProgress);
		
		data->rdWrInProgress=true;
	
		data->sendSingleBytes=true;
		OCTOSPI1->CR=(OCTOSPI1->CR & ~OCTOSPI_CR_FTHRES);
	
		data->sendQueue->enqueue(&data->sendQueue->data, command, osWaitForever);
		data->sendQueue->enqueue(&data->sendQueue->data, param, osWaitForever);
		data->sendQueue->enqueue(&data->sendQueue->data, 0, osWaitForever);

		OCTOSPI1->DLR = 2;
	
		OCTOSPI1->CR = (OCTOSPI1->CR & ~OCTOSPI_CR_FMODE);			//Functional mode: Indirect-write mode
			
		OCTOSPI1->TCR = (OCTOSPI1->TCR & ~OCTOSPI_TCR_DCYC);		//Number of dummy cycles: no cycles
		
		OCTOSPI1->CCR = (OCTOSPI1->CCR & ~OCTOSPI_CCR_ADMODE);		//Address mode: No address
		OCTOSPI1->CCR = (OCTOSPI1->CCR & ~OCTOSPI_CCR_DMODE) | OCTOSPI_CCR_DMODE_0;			//Data mode: Data on a signle line
		
		
		OCTOSPI1->CR |=OCTOSPI_CR_FTIE;		//treshold interupt enable
		OCTOSPI1->CR |=OCTOSPI_CR_TCIE;		//transfer complete interupt enable
		OCTOSPI1->CR |=OCTOSPI_CR_TEIE;	//transfer error interupt enable
			

}

bool writeExtRAMft8XX(PExtRamData *data, int dataToSend){

	int tabToSend[1];
	tabToSend[0]=dataToSend;
	return writeTabExtRAMft8XX(data, tabToSend, 1);
	
	
}

bool writeTabExtRAMft8XX(PExtRamData *data, int *dataToSend, int dataSize){

	if((data->openMode==WriteOnly || data->openMode==ReadWrite) && dataSize>0){
		
		while((OCTOSPI1->SR & OCTOSPI_SR_BUSY) || data->rdWrInProgress);
		
		data->rdWrInProgress=true;
		
		data->sendSingleBytes=false;
		OCTOSPI1->CR=(OCTOSPI1->CR & ~OCTOSPI_CR_FTHRES) | (3<<OCTOSPI_CR_FTHRES_Pos);
		
		OCTOSPI1->DLR = sizeof(int)*dataSize-1;
		
		for(int i=0; i<dataSize; i++){
			data->sendQueue->enqueue(&data->sendQueue->data, dataToSend[i], osWaitForever);
		}
		

		OCTOSPI1->CR = (OCTOSPI1->CR & ~OCTOSPI_CR_FMODE);			//Functional mode: Indirect-write mode
		OCTOSPI1->TCR = (OCTOSPI1->TCR & ~OCTOSPI_TCR_DCYC);		//Number of dummy cycles: no cycles
		OCTOSPI1->CCR = (OCTOSPI1->CCR & ~OCTOSPI_CCR_ADSIZE) | OCTOSPI_CCR_ADSIZE_1;  	//Address size: 24-bit address
		
		if(data->spiDataMode==QUAD_LINE){
			OCTOSPI1->CCR = (OCTOSPI1->CCR & ~OCTOSPI_CCR_ADMODE) | OCTOSPI_CCR_ADMODE_1 | OCTOSPI_CCR_ADMODE_0;		//Address mode: Address on four lines
			OCTOSPI1->CCR = (OCTOSPI1->CCR & ~OCTOSPI_CCR_DMODE) | OCTOSPI_CCR_DMODE_1 | OCTOSPI_CCR_DMODE_0;			 //Data mode: Data on four lines
		}else{
			OCTOSPI1->CCR = (OCTOSPI1->CCR & ~OCTOSPI_CCR_ADMODE) | OCTOSPI_CCR_ADMODE_0;		//Address mode: Address on a single line
			OCTOSPI1->CCR = (OCTOSPI1->CCR & ~OCTOSPI_CCR_DMODE) | OCTOSPI_CCR_DMODE_0;			//Data mode: Data on a signle line
		}
		
		OCTOSPI1->AR = (data->focusAdress & 0x3FFFFF) | (2<<22);		//in case the command needs an address (ADMODE!=00) and data (DMODE!=00), sending starts after writing the data to the DR register
		OCTOSPI1->CR |=OCTOSPI_CR_FTIE;		//treshold interupt enable
		OCTOSPI1->CR |=OCTOSPI_CR_TCIE;		//transfer complete interupt enable
		OCTOSPI1->CR |=OCTOSPI_CR_TEIE;	//transfer error interupt enable
			
		data->focusAdress+=sizeof(int)*dataSize;
		
		return true;
	}
	return false;
}



bool waitForReadyReadExtRAMft8XX(PExtRamData *data){

		if(data->getDataFlag==false){

			if(data->receiveQueue->dequeueTab(&data->receiveQueue->data, data->receiveData, data->nbrOfDataToTransfer, 0)){
				data->getDataFlag=true;

				return true;
			}  
		}
		
		return false;
	
}





