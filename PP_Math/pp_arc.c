#include "stdlib.h"
#include "pp_arc.h"


//double arcImplicitFunction(double X1, double Y1, double R2){

//			return (fpow_pp(Y1, 2)+fpow_pp(X1, 2)-R2);
//}

double arcImplicitFunction(double X, double Y, double R, unsigned int unit){

			double x=X/pow_pp(10, unit);
			double y=Y/pow_pp(10, unit);
			double r=R/pow_pp(10, unit);
	
			return (fpow_pp(y, 2)+fpow_pp(x, 2)-fpow_pp(r, 2))*pow_pp(10, unit);
}

//unsigned int calculateNrOfStepCircle(PXYdouble circleEndPoint, PXYdouble circleCenterPoint, PXYdouble circleStartPoint, double precisionX, double precisionY, defTurnCircle turnCircle){
//			unsigned int il_krok=0;
//			double R2=0;
//			PXYdouble pointBegin, pointEnd, pointTest;

//			pointBegin=subtractPointsXYdouble(circleStartPoint, circleCenterPoint);
//			pointTest=pointBegin;
//			pointEnd=subtractPointsXYdouble(circleEndPoint, circleCenterPoint);
//			
//			R2=fpow_pp(pointBegin.x, 2)+fpow_pp(pointBegin.y, 2);
//	
//	
//			while(!comparePointsXYdouble(pointTest, pointEnd, precisionX, precisionY)){
//				getNextStepPointOnArc(&pointTest, R2, precisionX, precisionY, turnCircle);
//		
//				il_krok++;
//				if(comparePointsXYdouble(pointTest, pointBegin, precisionX, precisionY)){
//					il_krok=0;
//					break;	//jeżeli okrąg jest źle zapisany i w trakcie obliczania ilości kroków wrócimy do tego samego miejsca to nie wykonuj łuku
//				}
//			};


//			return il_krok;
//}

unsigned int calculateNrOfStepCircle(PXY circleEndPoint, PXY circleCenterPoint, PXY circleStartPoint, unsigned int precisionX, unsigned int precisionY, unsigned int unit, defTurnCircle turnCircle){
			unsigned int il_krok=0;
			PXY pointBegin, pointEnd, pointTest;

			pointBegin=subtractPointsXY(circleStartPoint, circleCenterPoint);
			pointTest=pointBegin;
			pointEnd=subtractPointsXY(circleEndPoint, circleCenterPoint);
			
			int R=sqrt(fpow_pp(((double)pointBegin.x)/pow_pp(10, unit), 2)+fpow_pp(((double)pointBegin.y)/pow_pp(10, unit), 2))*pow_pp(10, unit);
	
	
			while(!comparePointsXY(pointTest, pointEnd)){
				pointTest=getNextStepPointOnArc(pointTest, R, precisionX, precisionY, unit, turnCircle);
		
				il_krok++;
				if(comparePointsXY(pointTest, pointBegin)){
					il_krok=0;
					break;	//jeżeli okrąg jest źle zapisany i w trakcie obliczania ilości kroków wrócimy do tego samego miejsca to nie wykonuj łuku
				}
			};


			return il_krok;
}

//PXYdouble getRealEndOfArc(PXYdouble circleEndPoint, PXYdouble circleCenterPoint, PXYdouble circleStartPoint, double precisionX, double precisionY, defTurnCircle turnCircle){
//			double min_odl=0xFFFFFFFF, odl_pom=0, R2;
//			PXYdouble pointEndReal, pointBegin, pointEnd, pointTest;
//				
//			pointBegin=subtractPointsXYdouble(circleStartPoint, circleCenterPoint);
//			pointTest=pointBegin;
//			pointEnd=subtractPointsXYdouble(circleEndPoint, circleCenterPoint);
//			pointEndReal=pointBegin;
//			
//			R2=fpow_pp(pointBegin.x, 2)+fpow_pp(pointBegin.y, 2);

//			do{
//				getNextStepPointOnArc(&pointTest, R2, precisionX, precisionY, turnCircle);
//		
//				odl_pom=fpow_pp(pointEnd.x-pointTest.x, 2)+fpow_pp(pointEnd.y-pointTest.y, 2);
//				if(odl_pom<min_odl){
//					pointEndReal=pointTest;
//					min_odl=odl_pom;
//				}

//			}while(!comparePointsXYdouble(pointTest, pointBegin, precisionX, precisionY));

//			pointEndReal=addPointsXYdouble(pointEndReal, circleCenterPoint);
//			
//			return pointEndReal;
//			

//}

PXY getRealEndOfArc(PXY circleEndPoint, PXY circleCenterPoint, PXY circleStartPoint, unsigned int precisionX, unsigned int precisionY, unsigned int unit, defTurnCircle turnCircle){
			double min_odl=0x7FFFFFFF, odl_pom=0;
			PXY pointEndReal, pointBegin, pointEnd, pointTest;
				
			pointBegin=subtractPointsXY(circleStartPoint, circleCenterPoint);
			pointTest=pointBegin;
			pointEnd=subtractPointsXY(circleEndPoint, circleCenterPoint);
			pointEndReal=pointBegin;
			
			int R=sqrt(fpow_pp(((double)pointBegin.x)/pow_pp(10, unit), 2)+fpow_pp(((double)pointBegin.y)/pow_pp(10, unit), 2))*pow_pp(10, unit);

			do{
				pointTest=getNextStepPointOnArc(pointTest, R, precisionX, precisionY, unit, turnCircle);
		
				odl_pom=fpow_pp((double)(pointEnd.x-pointTest.x)/pow_pp(10, unit), 2)+fpow_pp((double)(pointEnd.y-pointTest.y)/pow_pp(10, unit), 2);
				if(odl_pom<min_odl){
					pointEndReal=pointTest;
					min_odl=odl_pom;
				}

			}while(!comparePointsXY(pointTest, pointBegin));

			pointEndReal=addPointsXY(pointEndReal, circleCenterPoint);
			
			return pointEndReal;
			

}


//void getNextStepPointOnArc(PXYdouble *pointTest, double R2, double precisionX, double precisionY, defTurnCircle turnCircle){
//	
//				double halfPrecisionX, halfPrecisionY;
//	
//				halfPrecisionX=precisionX/2;
//				halfPrecisionY=precisionY/2;
//	
//				if(turnCircle==CLOCKWISE){
//					if(pointTest->y>0 && pointTest->x>=0 && pointTest->x<pointTest->y){												//opis II oktetu	
//						pointTest->x+=precisionX;
//						if(arcImplicitFunction(pointTest->x, pointTest->y-halfPrecisionY, R2)>=0){
//							pointTest->y-=precisionY; 
//						}
//					}else if(pointTest->y>0 && pointTest->x<0 && fabs_pp(pointTest->x)<=pointTest->y){					//opis III oktetu
//						pointTest->x+=precisionX;
//						if(arcImplicitFunction(pointTest->x, pointTest->y+halfPrecisionY, R2)<=0)pointTest->y+=precisionY;
//					}else if(pointTest->y<0 && pointTest->x<=0 && fabs_pp(pointTest->x)<fabs_pp(pointTest->y)){	//opis VI oktetu
//						pointTest->x-=precisionX;
//						if(arcImplicitFunction(pointTest->x, pointTest->y+halfPrecisionY, R2)>=0)pointTest->y+=precisionY;
//					}else if(pointTest->y<0 && pointTest->x>0 && pointTest->x<=fabs_pp(pointTest->y)){				//opis VII oktetu
//						pointTest->x-=precisionX;
//						if(arcImplicitFunction(pointTest->x, pointTest->y-halfPrecisionY, R2)<=0)pointTest->y-=precisionY; 
//					}
//					else if(pointTest->y>0 && pointTest->x>0 && pointTest->x>=pointTest->y){									//opis I oktetu	
//						pointTest->y-=precisionY;
//						if(arcImplicitFunction(pointTest->x+halfPrecisionX, pointTest->y, R2)<=0)pointTest->x+=precisionX;
//					}else if(pointTest->y<=0 && pointTest->x>0 && pointTest->x>fabs_pp(pointTest->y)){					//opis VIII oktetu
//						pointTest->y-=precisionY;
//						if(arcImplicitFunction(pointTest->x-halfPrecisionX, pointTest->y, R2)>=0)pointTest->x-=precisionX;
//					}else if(pointTest->y>=0 && pointTest->x<0 && fabs_pp(pointTest->x)>pointTest->y){					//opis IV oktetu
//						pointTest->y+=precisionY;
//						if(arcImplicitFunction(pointTest->x+halfPrecisionX, pointTest->y, R2)>=0)pointTest->x+=precisionX;
//					}else if(pointTest->y<0 && pointTest->x<0 && fabs_pp(pointTest->x)>=fabs_pp(pointTest->y)){	//opis V oktetu
//						pointTest->y+=precisionY;
//						if(arcImplicitFunction(pointTest->x-halfPrecisionX, pointTest->y, R2)<=0)pointTest->x-=precisionX;
//					}
//				}else{
//					if(pointTest->y>0 && pointTest->x>0 && pointTest->x<=pointTest->y){												//opis II oktetu	
//						pointTest->x-=precisionX;
//						if(arcImplicitFunction(pointTest->x, pointTest->y+halfPrecisionY, R2)<=0)pointTest->y+=precisionY;
//					}else if(pointTest->y>0 && pointTest->x<=0 && fabs_pp(pointTest->x)<pointTest->y){					//opis III oktetu
//						pointTest->x-=precisionX;
//						if(arcImplicitFunction(pointTest->x, pointTest->y-halfPrecisionY, R2)>=0)pointTest->y-=precisionY; 
//					}else if(pointTest->y<0 && pointTest->x<0 && fabs_pp(pointTest->x)<=fabs_pp(pointTest->y)){	//opis VI oktetu
//						pointTest->x+=precisionX;
//						if(arcImplicitFunction(pointTest->x, pointTest->y-halfPrecisionY, R2)<=0)pointTest->y-=precisionY;
//					}else if(pointTest->y<0 && pointTest->x>=0 && pointTest->x<fabs_pp(pointTest->y)){				//opis VII oktetu
//						pointTest->x+=precisionX;
//						if(arcImplicitFunction(pointTest->x, pointTest->y+halfPrecisionY, R2)>=0)pointTest->y+=precisionY;
//					}
//					else if(pointTest->y>=0 && pointTest->x>0 && pointTest->x>pointTest->y){									//opis I oktetu	
//						pointTest->y+=precisionY;
//						if(arcImplicitFunction(pointTest->x-halfPrecisionX, pointTest->y, R2)>=0)pointTest->x-=precisionX;
//					}else if(pointTest->y<0 && pointTest->x>0 && pointTest->x>=fabs_pp(pointTest->y)){					//opis VIII oktetu
//						pointTest->y+=precisionY;
//						if(arcImplicitFunction(pointTest->x+halfPrecisionX, pointTest->y, R2)<=0)pointTest->x+=precisionX;
//					}else if(pointTest->y>0 && pointTest->x<0 && fabs_pp(pointTest->x)>=pointTest->y){					//opis IV oktetu
//						pointTest->y-=precisionY;
//						if(arcImplicitFunction(pointTest->x-halfPrecisionX, pointTest->y, R2)<=0)pointTest->x-=precisionX;
//					}else if(pointTest->y<=0 && pointTest->x<0 && fabs_pp(pointTest->x)>fabs_pp(pointTest->y)){	//opis V oktetu
//						pointTest->y-=precisionY;
//						if(arcImplicitFunction(pointTest->x+halfPrecisionX, pointTest->y, R2)>=0)pointTest->x+=precisionX;
//					}
//				}
//	
//	//		return pointTest;
//}

PXY getNextStepPointOnArc(PXY pointTest, unsigned int radius, unsigned int precisionX, unsigned int precisionY, unsigned int unit, defTurnCircle turnCircle){
	
				double halfPrecisionX, halfPrecisionY;
	
				halfPrecisionX=(double)precisionX/2;
				halfPrecisionY=(double)precisionY/2;
	
				if(turnCircle==CLOCKWISE){
					if(pointTest.y>0 && pointTest.x>=0 && pointTest.x<pointTest.y){												//opis II oktetu	
						pointTest.x+=precisionX;
						if(arcImplicitFunction(pointTest.x, (double)pointTest.y-halfPrecisionY, radius, unit)>=0){
							pointTest.y-=precisionY; 
						}
					}else if(pointTest.y>0 && pointTest.x<0 && fabs_pp(pointTest.x)<=pointTest.y){					//opis III oktetu
						pointTest.x+=precisionX;
						if(arcImplicitFunction(pointTest.x, (double)pointTest.y+halfPrecisionY, radius, unit)<=0)pointTest.y+=precisionY;
					}else if(pointTest.y<0 && pointTest.x<=0 && fabs_pp(pointTest.x)<fabs_pp(pointTest.y)){	//opis VI oktetu
						pointTest.x-=precisionX;
						if(arcImplicitFunction(pointTest.x, (double)pointTest.y+halfPrecisionY, radius, unit)>=0)pointTest.y+=precisionY;
					}else if(pointTest.y<0 && pointTest.x>0 && pointTest.x<=fabs_pp(pointTest.y)){				//opis VII oktetu
						pointTest.x-=precisionX;
						if(arcImplicitFunction(pointTest.x, (double)pointTest.y-halfPrecisionY, radius, unit)<=0)pointTest.y-=precisionY; 
					}
					else if(pointTest.y>0 && pointTest.x>0 && pointTest.x>=pointTest.y){									//opis I oktetu	
						pointTest.y-=precisionY;
						if(arcImplicitFunction((double)pointTest.x+halfPrecisionX, pointTest.y, radius, unit)<=0)pointTest.x+=precisionX;
					}else if(pointTest.y<=0 && pointTest.x>0 && pointTest.x>fabs_pp(pointTest.y)){					//opis VIII oktetu
						pointTest.y-=precisionY;
						if(arcImplicitFunction((double)pointTest.x-halfPrecisionX, pointTest.y, radius, unit)>=0)pointTest.x-=precisionX;
					}else if(pointTest.y>=0 && pointTest.x<0 && fabs_pp(pointTest.x)>pointTest.y){					//opis IV oktetu
						pointTest.y+=precisionY;
						if(arcImplicitFunction((double)pointTest.x+halfPrecisionX, pointTest.y, radius, unit)>=0)pointTest.x+=precisionX;
					}else if(pointTest.y<0 && pointTest.x<0 && fabs_pp(pointTest.x)>=fabs_pp(pointTest.y)){	//opis V oktetu
						pointTest.y+=precisionY;
						if(arcImplicitFunction((double)pointTest.x-halfPrecisionX, pointTest.y, radius, unit)<=0)pointTest.x-=precisionX;
					}
				}else{
					if(pointTest.y>0 && pointTest.x>0 && pointTest.x<=pointTest.y){												//opis II oktetu	
						pointTest.x-=precisionX;
						if(arcImplicitFunction(pointTest.x, (double)pointTest.y+halfPrecisionY, radius, unit)<=0)pointTest.y+=precisionY;
					}else if(pointTest.y>0 && pointTest.x<=0 && fabs_pp(pointTest.x)<pointTest.y){					//opis III oktetu
						pointTest.x-=precisionX;
						if(arcImplicitFunction(pointTest.x, (double)pointTest.y-halfPrecisionY, radius, unit)>=0)pointTest.y-=precisionY; 
					}else if(pointTest.y<0 && pointTest.x<0 && fabs_pp(pointTest.x)<=fabs_pp(pointTest.y)){	//opis VI oktetu
						pointTest.x+=precisionX;
						if(arcImplicitFunction(pointTest.x, (double)pointTest.y-halfPrecisionY, radius, unit)<=0)pointTest.y-=precisionY;
					}else if(pointTest.y<0 && pointTest.x>=0 && pointTest.x<fabs_pp(pointTest.y)){				//opis VII oktetu
						pointTest.x+=precisionX;
						if(arcImplicitFunction(pointTest.x, (double)pointTest.y+halfPrecisionY, radius, unit)>=0)pointTest.y+=precisionY;
					}
					else if(pointTest.y>=0 && pointTest.x>0 && pointTest.x>pointTest.y){									//opis I oktetu	
						pointTest.y+=precisionY;
						if(arcImplicitFunction((double)pointTest.x-halfPrecisionX, pointTest.y, radius, unit)>=0)pointTest.x-=precisionX;
					}else if(pointTest.y<0 && pointTest.x>0 && pointTest.x>=fabs_pp(pointTest.y)){					//opis VIII oktetu
						pointTest.y+=precisionY;
						if(arcImplicitFunction((double)pointTest.x+halfPrecisionX, pointTest.y, radius, unit)<=0)pointTest.x+=precisionX;
					}else if(pointTest.y>0 && pointTest.x<0 && fabs_pp(pointTest.x)>=pointTest.y){					//opis IV oktetu
						pointTest.y-=precisionY;
						if(arcImplicitFunction((double)pointTest.x-halfPrecisionX, pointTest.y, radius, unit)<=0)pointTest.x-=precisionX;
					}else if(pointTest.y<=0 && pointTest.x<0 && fabs_pp(pointTest.x)>fabs_pp(pointTest.y)){	//opis V oktetu
						pointTest.y-=precisionY;
						if(arcImplicitFunction((double)pointTest.x+halfPrecisionX, pointTest.y, radius, unit)>=0)pointTest.x+=precisionX;
					}
				}
	
			return pointTest;
}
