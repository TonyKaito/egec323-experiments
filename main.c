#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// -------------------------------------------------------------THE ACTUAL COURSE CONTENT-----------------------------------------
double derivative(double (*f)(double), double x0)
{
	const double delta = 1.0e-7;
	double x_2 = x0 + delta;
	double x_1 = x0 - delta;
	double y_2 = f(x_2);
	double y_1 = f(x_1);
	return (y_2 - y_1) / (x_2 - x_1);
}

double integral(double (*f)(double), double a, double b) // SIMPSON'S RULE
{
	int n = 1e7; // hardcoded, usually a parameter
	double delta_x = (b - a) / n;
	double sum = f(a) + f(b);
	
	for (int i = 1; i < n - 1; ++i)
	{
		double x = a + (i * delta_x);
		if (i % 2 == 1)
		{
			sum += 4 * f(x);
		}
		else {
			sum += 2 * f(x);
		}
	}
	return (delta_x / 3) * sum;
}

int comp_dbl(const void* a, const void* b) // needed for qsort
{
	double* x = (double*) a;
	double* y = (double*) b;
	if(*x < *y) return -1;
	if(*y < *x) return 1;
	return 0;
}

void apply_randvar_func(const double* input, double* output, int size, double (*f)(double))
{
	for (int i = 0; i < size; ++i)
	{
		output[i] = f(input[i]);
	}
}
// ------------------------------------------------------------------TEST FUNCTIONS-----------------------------------------------------
double square(double x)
{
	return x*x;
}

double unit(double value)
{
	if (value < 0) return 0;
	return 1;
}

double pulse(double value, double bandwidth)
{
	return unit(value) - unit(value - bandwidth);
}

double impulse(double value)
{
	const double delta = 1.0e-6;
	return (1/delta) * pulse(value, delta);
}

int main(void)
{
	double x = 3;
	double f_2 = square(x);
	double df_2 = derivative(square, x);
	double F_2 = integral(square, 0, 1);
	printf("%f then %f\n", f_2, df_2);
	printf("%f and then %f\n", f_2, F_2);
	
	double arr[] = {6, 4, 7, 75, 17, 57};
	double output[6];
	qsort(arr, sizeof(arr)/sizeof(arr[0]), sizeof(arr[0]), comp_dbl);
	apply_randvar_func(arr, output, 6, square);
	for (size_t i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
	{
		printf("%f %f\n", arr[i], output[i]);
	}
	
	double thing = 1;
	double df_thing = derivative(unit, thing);
	double delta_thing = impulse(thing);
	double Delta_thing = integral(impulse, -8.0f, thing);
	printf("---------\n");
	printf("%f %f\n", df_thing, delta_thing);
	printf("%f %f\n", unit(thing), Delta_thing);
	
	printf("Hello World\n");
	return 0;
}