#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<ctype.h>
#include<Windows.h>
#include<math.h>
#include<conio.h>

/*
170729 Update까지 구현함.
여태까지 배운 점
함수의 매개변수 유효성과 그 반환값의 유효성을 검사하고 또 검사하는
일종의 체크 체인같은걸 만들어야 프로그램이 안전해짐.
*/
//버퍼 크기 관련
#define COMMON_LENGTH 600
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
#define IMPROPER_INPUT(B) \
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
#define SET_COLOR(X) \
(SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),(X)))
#define SET_COLOR_DEFAULT		SET_COLOR(WHITE)
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
#define NO_STRING_INPUT(B) \
((B)[0] == (char)NULL)
#define STRING_INPUT(B) \
((B)[0] != (char)NULL)
#define INT_LIMIT_LENGTH 10
//여기서 임시로 버퍼를 만들어주니까 따로 선언할 필요가 없다.
#define INPUT_SELECT \
{char temp[COMMON_LENGTH] = { 0 }; \
printf("> ");\
SET_COLOR(ORDER_COLOR); \
gets_s(temp, COMMON_LENGTH); \
SET_COLOR_DEFAULT; \
select = Input_String_Then_Return_Integer(temp);}
//가장 많이 쓰이는 매크로함수///////////////////////////////////
#define BEFORE_RETURN_PRINT_(M) \
{printf("%s",(M)); \
return;}
/////////////////////////////////////////////////////////////
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
//선택한 번호로 인해 명령이 취소되는 여러 경우를 매크로로 묶어서 정의해둠.
#define COMMON_CANCEL_REASON(M) \
		NO_INPUT: \
BEFORE_RETURN_PRINT_(MESSAGE_NO_INPUT(M)); \
case NOT_A_NUMBER: \
BEFORE_RETURN_PRINT_(MESSAGE_INPUT_ISNT_NUMBER(M)); \
case OUT_OF_RANGE: \
BEFORE_RETURN_PRINT_(MESSAGE_OUT_OF_RANGE(M)); 
#define COMMON_STRING_INPUT_CANCEL_REASON(B, M) \
if (NO_STRING_INPUT(B)) \
BEFORE_RETURN_PRINT_(MESSAGE_NO_INPUT(M)); \
if (IMPROPER_INPUT(B)) \
BEFORE_RETURN_PRINT_(MESSAGE_SYSTEM_INVAIDING_INPUT(M));
//X 는 MIN, Y는 MAX (X~Y)
#define RANDOM(X,Y) \
((rand() % ((Y+1) - (X))) + X)
#define ORDER_IS_(X)	\
!strcmp(Order, (X))
///////////////////////////////////////////////////
///////////////////////////////////////////////////

/*추가 개발하고자 하는 사항
1.  종료 전에 동적할당한 것들 해제해주기
*/