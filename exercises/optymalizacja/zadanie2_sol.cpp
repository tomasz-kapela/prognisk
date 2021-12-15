
void obliczSSE(float * wynik, float *a, float *b, float x, int n){
   for(int i=0; i<n; i++){
	   if(a[i] == b[i] ){
		   wynik[i] = x + b[i]*x*x;
	   } else if(a[i] > b[i]){
		   wynik[i] = b[i]/(a[i]-b[i])*x + b[i]*x*x;
	   } else {
		   wynik[i] = a[i]/(b[i]-a[i])*x + b[i]*x*x;
	   }
   }
}
