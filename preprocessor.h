#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<ctype.h>
#include<Windows.h>
#include<math.h>
#include<conio.h>


//버퍼 크기 관련
#define COMMON_LENGTH 100	//_UPDATE_TIME: 레이블의 시간 문자열보다는 길어야한다.
#define COMMON_LENGTH_EXTENDED 250	//버퍼기록용
#define SITE_NAME_LENGTH	COMMON_LENGTH
#define ID_LENGTH					COMMON_LENGTH
#define PASSWORD_LENGTH	COMMON_LENGTH
#define UPDATE_TIME_SIZE		COMMON_LENGTH
#define MEMO_LENGTH			COMMON_LENGTH
#define ORDER_LENGTH			COMMON_LENGTH
//파일 I/O 기호 및 매직넘버 관련
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
//아무것도 입력하지 않고 엔터를 눌렀다면
#define NO_INPUT -1
//범위를 벗어난 숫자가 입력되었다면
#define OUT_OF_RANGE -2
//숫자말고 딴거 입력했으면
#define NOT_A_NUMBER -3
#define SO_BIG_TO_RETURN_INTEGER -4
#define INTENDED_ZERO -5
#define SYSTEM_CHAR_INPUT -6
#define _NOT_A_NUMBER(X) ((X) > '9' || (X) < '0') 
//시스템 조작 문자가 포함되었는지 검사
#define PROHIBITED_INPUT(B) \
(Is_Buffer_Contain_Operator_Symbol((B)) == TRUE)
//텍스트 색상 관련
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
//사이트 및 계정 선택 관련
#define UNIVERSAL_ZERO 0
#define MAKE_NEW_SITE		UNIVERSAL_ZERO
#define CANCEL_UPDATE		UNIVERSAL_ZERO
#define CHANGE_SITE_NAME	UNIVERSAL_ZERO
#define CANCEL_DELETE			UNIVERSAL_ZERO
#define DELETE_SITE				UNIVERSAL_ZERO
#define CANCEL_SWAP		UNIVERSAL_ZERO
//프로그램 상태 관련
#define START_PROGRAM '0'
#define INPUT_SITE_NAME '1'
#define INPUT_ACCOUNT_ID '2'
#define INPUT_ACCOUNT_PW '3'
#define INPUT_ACCOUNT_CURRENT_UPDATE '4'
#define INPUT_ACCOUNT_MEMO '5'
#define END_INPUT_SITE '6'
#define END_PROGRAM '9'
#define NULL_MESSAGE "(null)"
//자연어 관련
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
//기타
#define MAKE_BUFFER(X) \
char (X)[COMMON_LENGTH] = { 0 };
#define MAKE_EXTENDED_BUFFER(X) \
char (X)[COMMON_LENGTH_EXTENDED] = { 0 };
#define NO_STRING_INPUT(B) \
((B)[0] == (char)NULL)

#define STRING_INPUT(B) \
((B)[0] != (char)NULL)

#define INT_LIMIT_LENGTH 10

//입력을 문자열로서 받아 변수에 정수로서 저장한다.
#define INPUT_SELECT(S) \
{char temp[COMMON_LENGTH] = { 0 }; \
printf("> ");\
SET_CONSOLE_COLOR(ORDER_COLOR); \
Get_String_Without_Buffer_Overflow(temp); \
SET_CONSOLE_COLOR_DEFAULT; \
S = Input_String_Then_Return_Integer(temp);}

//가장 많이 쓰이는 매크로함수///////////////////////////////////
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
#M " 취소\n"
#define MESSAGE_FAIL(M) \
#M " 실패\n"
#define MESSAGE_SUCCESS(M) \
#M " 성공\n"
#define MESSAGE_NO_INPUT(M) \
"입력이 없으므로 " #M " 취소.\n"
#define MESSAGE_INPUT_ISNT_NUMBER(M) \
"숫자 외의 문자가 입력되었으므로 " #M " 취소.\n"
#define MESSAGE_OUT_OF_RANGE(M) \
"입력된 수가 범위를 벗어났으므로 " #M " 취소.\n"
#define MESSAGE_WRONG_INPUT(M) \
"잘못된 입력으로 인해 포인터가 반환되지 않았으므로 " #M " 취소.\n"
#define MESSAGE_SYSTEM_INVAIDING_INPUT(M) \
"'#' , '$', '%' 등의 잘못된 입력으로 인해 " #M " 취소.\n"
#define MESSAGE_UNKNOWN_ERROR(M) \
"예상치 못한 오류로 " #M " 취소.\n"

/*
선택한 번호로 인해 명령이 취소되는 여러 경우를 매크로로 묶어서 정의해둠.
입력이 없거나, 입력이 숫자가 아니거나, 유효한 범위가 아니거나.
*/
#define COMMON_CANCEL_REASON(M) \
		NO_INPUT: \
BEFORE_RETURN_PRINT_(MESSAGE_NO_INPUT(M)); \
case NOT_A_NUMBER: \
BEFORE_RETURN_PRINT_(MESSAGE_INPUT_ISNT_NUMBER(M)); \
case OUT_OF_RANGE: \
BEFORE_RETURN_PRINT_(MESSAGE_OUT_OF_RANGE(M)); 

//입력받은 문자열이 업데이트될 문자열로 쓰일 수 없을 경우 업데이트를 취소한다.
#define COMMON_STRING_INPUT_CANCEL_REASON(B, M) \
if (NO_STRING_INPUT(B)) \
BEFORE_RETURN_PRINT_(MESSAGE_NO_INPUT(M)); \
if (PROHIBITED_INPUT(B)) \
BEFORE_RETURN_PRINT_(MESSAGE_SYSTEM_INVAIDING_INPUT(M));
//X 는 MIN, Y는 MAX (X~Y)
#define RANDOM(X,Y) \
((rand() % ((Y+1) - (X))) + X)
#define ORDER_IS_(X)	\
(!strcmp(Order, (X)))
///////////////////////////////////////////////////
///////////////////////////////////////////////////

/*추가 개발하고자 하는 사항


*/