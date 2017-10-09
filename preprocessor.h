#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<ctype.h>
#include<Windows.h>
#include<math.h>
#include<conio.h>


//���� ũ�� ����
#define COMMON_LENGTH 100	//_UPDATE_TIME: ���̺��� �ð� ���ڿ����ٴ� �����Ѵ�.
#define COMMON_LENGTH_EXTENDED 250	//���۱�Ͽ�
#define SITE_NAME_LENGTH	COMMON_LENGTH
#define ID_LENGTH					COMMON_LENGTH
#define PASSWORD_LENGTH	COMMON_LENGTH
#define UPDATE_TIME_SIZE		COMMON_LENGTH
#define MEMO_LENGTH			COMMON_LENGTH
#define ORDER_LENGTH			COMMON_LENGTH
//���� I/O ��ȣ �� �����ѹ� ����
#define START_OP '#'
#define END_OP '$'
#define EMPTY_OP '%'
#define ASCII_BELL 7
#define STORE_NORMAL_DATA_TO_THE_BUFFER 10
#define WAIT_FOR_OPERATION_NUMBER 11
#define INPUT_DATA_FROM_NOW 12
#define PASS_BUFFER_TO_PROPER_POSITION 13
#define SITE_AND_ACCOUNTS 14
#define SITE_ONLY 15
#define HISTORY_ADD 20
#define HISTORY_DELETE 21
#define HISTORY_UPDATE 22
#define HISTORY_SWAP 23
#define HISTORY_NOTHING 24
#define ENTIRE_TYPE 30
#define DIGIT_ONLY 31
#define ALPHABET_ONLY 32
#define LOOK_NORMALLY_CHAR 33
//�ƹ��͵� �Է����� �ʰ� ���͸� �����ٸ�
#define NO_INPUT -1
//������ ��� ���ڰ� �ԷµǾ��ٸ�
#define OUT_OF_RANGE -2
//���ڸ��� ���� �Է�������
#define NOT_A_NUMBER -3
#define SO_BIG_TO_RETURN_INTEGER -4
#define INTENDED_ZERO -5
#define SYSTEM_CHAR_INPUT -6
#define _NOT_A_NUMBER(X) ((X) > '9' || (X) < '0') 
//�ý��� ���� ���ڰ� ���ԵǾ����� �˻�
#define PROHIBITED_INPUT(B) \
(Is_Buffer_Contain_Operator_Symbol((B)) == TRUE)
//�ؽ�Ʈ ���� ����
#define YELLOW	14
#define PINK		13
#define RED			12
#define SKY			11
#define GREEN		10
#define BLUE		9
#define GRAY		8
#define WHITE		7
#define DARK_YELLOW 6
#define PURPLE	5
#define BLACK		0
#define SET_CONSOLE_COLOR(X) \
(SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),(X)))
#define SET_CONSOLE_COLOR_DEFAULT		SET_CONSOLE_COLOR(WHITE)
#define ACTIVE_ZERO_COLOR			GREEN
#define ORDER_COLOR					RED
#define HISTORY_COLOR				PINK
#define SITE_BASIC_COLOR				YELLOW
#define ACCOUNT_BASIC_COLOR	DARK_YELLOW
//����Ʈ �� ���� ���� ����
#define UNIVERSAL_ZERO 0
#define MAKE_NEW_SITE		UNIVERSAL_ZERO
#define CANCEL_UPDATE		UNIVERSAL_ZERO
#define CHANGE_SITE_NAME	UNIVERSAL_ZERO
#define CANCEL_DELETE			UNIVERSAL_ZERO
#define DELETE_SITE				UNIVERSAL_ZERO
#define CANCEL_SWAP		UNIVERSAL_ZERO
//���α׷� ���� ����
#define START_PROGRAM '0'
#define INPUT_SITE_NAME '1'
#define INPUT_ACCOUNT_ID '2'
#define INPUT_ACCOUNT_PW '3'
#define INPUT_ACCOUNT_CURRENT_UPDATE '4'
#define INPUT_ACCOUNT_MEMO '5'
#define END_INPUT_SITE '6'
#define END_PROGRAM '9'
#define NULL_MESSAGE "(null)"
//�ڿ��� ����
#define NOT_JUNK 0
#define JUNK 1
#define DONT_SHOW_LIST 0
#define SHOW_LIST 1
#define NOTHING_POINTER NULL
#define ONE_BYTE 1
#define ONCE 1
#define YES 1
#define NO 0
#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAIL 0
#define FIRST 1
#define DO_NOTHING  
//��Ÿ
#define MAKE_BUFFER(X) \
char (X)[COMMON_LENGTH] = { 0 };
#define MAKE_EXTENDED_BUFFER(X) \
char (X)[COMMON_LENGTH_EXTENDED] = { 0 };
#define NO_STRING_INPUT(B) \
((B)[0] == (char)NULL)

#define STRING_INPUT(B) \
((B)[0] != (char)NULL)

#define INT_LIMIT_LENGTH 10

//�Է��� ���ڿ��μ� �޾� ������ �����μ� �����Ѵ�.
#define INPUT_SELECT(S) \
{char temp[COMMON_LENGTH] = { 0 }; \
printf("> ");\
SET_CONSOLE_COLOR(ORDER_COLOR); \
Get_String_Without_Buffer_Overflow(temp); \
SET_CONSOLE_COLOR_DEFAULT; \
S = Input_String_Then_Return_Integer(temp);}

//���� ���� ���̴� ��ũ���Լ�///////////////////////////////////
#define BEFORE_RETURN_PRINT_(M) \
{printf("%s",(M)); \
return;}

#define BEFORE_RETURN_INTEGER_PRINT_(M,I) \
{printf("%s",(M)); \
return (I);}
#define BEFORE_EXIT_PRINT_(M) \
{printf("%s",(M)); \
exit(0);}
#define __________PRINT_DEVIDE_LINE__________ \
printf("--------------------------------------------------\n")
#define PRINT_DEVIDE_THICK_LINE \
printf("===================================================\n")
#define DB_EMPTY \
(root->first_Site == NULL)
#define HISTORY_EMPTY \
(clue->first == NULL)
#define MESSAGE_CANCEL(M) \
#M " ���\n"
#define MESSAGE_FAIL(M) \
#M " ����\n"
#define MESSAGE_SUCCESS(M) \
#M " ����\n"
#define MESSAGE_NO_INPUT(M) \
"�Է��� �����Ƿ� " #M " ���.\n"
#define MESSAGE_INPUT_ISNT_NUMBER(M) \
"���� ���� ���ڰ� �ԷµǾ����Ƿ� " #M " ���.\n"
#define MESSAGE_OUT_OF_RANGE(M) \
"�Էµ� ���� ������ ������Ƿ� " #M " ���.\n"
#define MESSAGE_WRONG_INPUT(M) \
"�߸��� �Է����� ���� �����Ͱ� ��ȯ���� �ʾ����Ƿ� " #M " ���.\n"
#define MESSAGE_SYSTEM_INVAIDING_INPUT(M) \
"'#' , '$', '%' ���� �߸��� �Է����� ���� " #M " ���.\n"
#define MESSAGE_UNKNOWN_ERROR(M) \
"����ġ ���� ������ " #M " ���.\n"

/*
������ ��ȣ�� ���� ����� ��ҵǴ� ���� ��츦 ��ũ�η� ��� �����ص�.
�Է��� ���ų�, �Է��� ���ڰ� �ƴϰų�, ��ȿ�� ������ �ƴϰų�.
*/
#define COMMON_CANCEL_REASON(M) \
		NO_INPUT: \
BEFORE_RETURN_PRINT_(MESSAGE_NO_INPUT(M)); \
case NOT_A_NUMBER: \
BEFORE_RETURN_PRINT_(MESSAGE_INPUT_ISNT_NUMBER(M)); \
case OUT_OF_RANGE: \
BEFORE_RETURN_PRINT_(MESSAGE_OUT_OF_RANGE(M)); 

//�Է¹��� ���ڿ��� ������Ʈ�� ���ڿ��� ���� �� ���� ��� ������Ʈ�� ����Ѵ�.
#define COMMON_STRING_INPUT_CANCEL_REASON(B, M) \
if (NO_STRING_INPUT(B)) \
BEFORE_RETURN_PRINT_(MESSAGE_NO_INPUT(M)); \
if (PROHIBITED_INPUT(B)) \
BEFORE_RETURN_PRINT_(MESSAGE_SYSTEM_INVAIDING_INPUT(M));
//X �� MIN, Y�� MAX (X~Y)
#define RANDOM(X,Y) \
((rand() % ((Y+1) - (X))) + X)
#define ORDER_IS_(X)	\
(!strcmp(Order, (X)))
///////////////////////////////////////////////////
///////////////////////////////////////////////////

/*�߰� �����ϰ��� �ϴ� ����


*/