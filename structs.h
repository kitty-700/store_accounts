typedef struct Account_Element
{
	struct Account_Element * next;
	char ID[ID_LENGTH];
	char PW[PASSWORD_LENGTH];
	char Update_Time[UPDATE_TIME_SIZE];	//������ ������Ʈ ����
	char Memo[MEMO_LENGTH];
}Account_Element;
typedef struct Site_Account
{
	Account_Element * head;
	struct Site_Account * next;
	int how_many_accounts;
	char Site_Name[SITE_NAME_LENGTH];
}Site_Account;	//���Ḯ��Ʈ�� �̿��Ͽ� ������ ����Ʈ�� � ���̵���� �ִ��� �����Ѵ�.
typedef struct DB
{
	Site_Account * first_Site;
	int how_many_sites;
}DB;
typedef struct Change_What_Thing
{
	struct Change_What_Thing * next;
	int change_operator;
	char change_from[COMMON_LENGTH_EXTENDED];
	char change_to[COMMON_LENGTH_EXTENDED];
}Change_Something;

typedef struct History
{
	Change_Something * first;	//�о�� �� �������
	Change_Something * last;	//�ۼ��� �� ���⿡
	int how_many_changes;
}History;

typedef enum Order_Type
{
	add_something,			//a	
	clear_display,				//c
	delete_something,		//d
	help,							//h , ?
	show_change_history,	//l
	do_nothing,					//n
	quite_program	,			//q
	re_import,					//r
	show_site_list,				//s
	update_something,		//u
	swap_site_order,			//w
	export_data,					//x
	show_account_list,
	no_input,
	unset_DB,
	unset_history,
	undefined_order,
	show_account_through_number
}Order_Type;