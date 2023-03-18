#include "credit.h"
#include "s21_calc.h"
// #include "check_function.c"
// int *ptr = array;   // указатель ptr хранит адрес первого элемента массива
// array
//     ptr = ptr + 2;      // перемезаем указатель на 2 элемента вперед
// sin(2*(2*2))
// "()sin(1*2*3(8)"
// "((sin(1*2*3(8))"

// "(sin(1*2*38+))"
//  3 + 4 × 2 ÷ ( 1 − 5 ) ^ 2 ^ 3
// 3*(5+6)-2*4-(8*9/3-6)
// /0
// 3-(5+6)/(2+4)-8*9-6/7-2*3
// 2^2^2

// exit 1 некорректный ввод
// Деление на 0;
// ошибка в передования показателях в функции (ышт)

void main() {
  int err = FAIL;
  // Stack_t stack;
  Stack_t stack = {0};  // Правильно нужно сделать массивом)
  stack.size = 0;
  // *stack.data = 0;
  char *str = "sin(5)";  // -77.6904761904761905 Работает и так и char str [100]
                         // = "4.2001";
  char *str_ch = "I";
  char str_x[SIZE] = "-1";
  // double  str_x = 2.2;
  // str_x = "2.2";

  char str_v[SIZE];
  str_ch = str_v;
  char *val = "Yrr";
  val = str_v;
  // str_ch [SIZE] = "4.2001";

  double *num;
  // num = 999.9;
  // double  *num5;
  // *num5 = 899.9;
  // char str5[] = "8.255645343";
  double num_v = 1.1;
  // double value = 9666;
  num = &num_v;
  // push(&stack, value);
  // parser(str);
  int *count;
  int count_v = 0;
  count = &count_v;
  char tmp3;
  // *count = 1;

  double stro[10] = {0};
  double numb = 9;
  stro[0] = numb;

  // char val_v[3] ="pop";
  // char *pval = &val_v[3];
  // *pval = 's';

  // printf("OOOOOONumber_main_0[[[0]]] -  {%s} \n", val);
  // val = &val_v;

  // tmp = types(str, count, &val);
  /*// tmp = types(str, count, val);
  printf("Number_main_1 - %.7f -  {%s}\n", *num,  str);*/
  // printf("Number_main_00 - %d -  {{%s}} - %c - {{%s}}\n", *count,  val, tmp,
  // str);
  /* // printf("Number_main_00 - %d -  {%s} - %c - {%s}\n", *count,  val_v, tmp,
str);
   // printf("Number_main_00 - %d -  {%s} - %c - {%s}\n", *count,  pval, tmp,
str);

   // printf("Number_main_3 - %.8f -  {%s}\n", *num,  str);
   // err=number(str5, num5);
   // printf("Check 2 %f, -  {%s}\n", *num5, str5);
   // num2 = *num;
 // printf("Number - %d - %.7f {%s}\n", number (str, num), &num2, str);
//    printf("Number - %lf -  {%s}\n", num,  str);
 // pop(&stack);
 // pop(&stack);
 // _getch();
*/

  //   char num1[80], num2[80];

  //   printf("Введите первое число: ");
  //   gets(num1);
  //   printf("Введите второе число: ");
  //   gets(num2);
  //   printf("Сумма: %lf", atof(num1) + atof(num2));
  // printf("EXIT - %d\n", err);

  // int fun = s21_calc (str, num);

  // printf("Функция предыдущий следующий символ - %c\n",
  // previous_next_character(1, "2+9", *count, tmp)); types(str, count, str_ch);
  // int t = strlen(val);
  // printf("Работа парсера_fun:  ----{{%s}} = %d\n",   val, t);

  // count_v = 0;

  // push(&stack, val);
  // printf("CH_STACK->DATA_ch[1]: %s \n", stack.data[1]);

  // *count = 4;
  // types(str, count, str_ch);
  // push(&stack, val);
  // printf("CH_STACK->DATA[2]: %s \n", stack.data[2]);

  // *count = 5;
  // types(str, count, str_ch);
  // push(&stack, val);
  // printf("CH_STACK->DATA[3]: %s \n", stack.data[3]);

  // *count = 6;
  // types(str, count, str_ch);
  // push(&stack, val);
  // printf("CH_STACK->DATA[1]: %s \n", stack.data[1]);

  // printf("Работа парсера_main:  %d - {{%s}}\n", fun, str_ch);
  // printf ("Работа парсера: %c - {{%s}}", parser(str, str_ch), str_ch);
  // printvalue_stack (6);

  // Stack_t stack;
  // stack.size = 0;

  // push(&stack, val);
  // printstack(&stack);
  // push(&stack, val);
  // printstack(&stack);
  // push(&stack, 7);
  // printstack(&stack, printvalue_stack);
  // printf("%d\n", pop(&stack));
  // printstack(&stack, printvalue_stack);
  // printf("%d\n", pop(&stack));
  // printstack(&stack, printvalue_stack);
  // printf("%d\n", pop(&stack));
  // printstack(&stack, printvalue_stack);
  // _getch();

  // else if (str[vr] > 48 && str[vr] <= 57 || (str[n] == 46)) {

  // // Проверка до после символ
  //   char str1[] = "0.345";
  // //   // char *str1 = "0.3465";
  // //   printf("Check 1:: %d, -  {%s} - '%s'\n", *count, str1, str_v);
  //   count_v = 0;
  //   char tmp = previous_next_character(-1, str1, count_v, val);
  //   // previous_next_character(-1, str1, 0, val);
  // //   // printf("\n\n\n\n\nCheck 2 %f, -  {%s}\n", *num, str1);
  // //   printf("Функция сравнения строк: %d\n", strcmp(val, "."));

  //   printf("Check 2:: %d, -  {%s} - '%s', exit prev: %d\n", *count, str1,
  //   val, tmp);

  credit_t credit_N[10];
  credit_N->type = 2;
  credit_N->total_credit = 60000;
  credit_N->period = 6;
  credit_N->period_uom = 'm';  // y - year, m - month
  credit_N->percent_rate = 24;
  credit_N->total_overpayment = 0.0;
  credit_N->overpayment = 0.0;
  credit_N->month_min = 0.0;
  credit_N->month_max = 0.0;

  calc_credit(credit_N);

  // fun = previous_next_character(-1, str, 0, val);
  double num3[SIZE];
  int z = number(str, num3);
  int fun = check_number(str);
  int fun2 = number(str, num);
  int fun3 = parser(str, &stack);
  int fun4 = s21_calc(str, str_x, stro);
  // double test = pow(-3, 3);
  // printf("\nCheck_number - %d - {%s}  ----- %f\n", fun,  str, test);
  printf("Number - %d  -- XXXX - %s\n", fun2, &stack.x);
  printf("Парсер - %d  -- XXXX - %s\n", fun3, &stack.x);
  printf("Calc - %d  -- XXXX - %s\n", fun4, &stack.x);

  printf("\natof - %f\n", atof(".2"));
}