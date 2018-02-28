int main() {
	int a[] = {3,2,5,6,7};
	int i, j;
	for( i = 1; i < 5; i++) {
		for(j = 1; j < 5; i++){
			if (a[i] > a[j]) {
			a[i] = a[i]^a[j];
			a[j] = a[j]^a[i];
			a[i] = a[i]^a[j];
			}	
		}
	}
}
