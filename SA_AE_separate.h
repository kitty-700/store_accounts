int Select_SA_Number(DB * root, char general_message[COMMON_LENGTH], char active_zero_message[COMMON_LENGTH], int is_show_SA);
int Select_AE_Number(Site_Account * SA, char general_message[COMMON_LENGTH], char active_zero_message[COMMON_LENGTH], int is_show_AE);
int Select_AE_Attribute(char general_message[COMMON_LENGTH], char active_zero_message[COMMON_LENGTH]);

void Show_SA(const DB * root, const int present_how);
void Show_AE(const Site_Account * SA);

void Attach_SA_to_the_DB(Site_Account* SA_to_insert, DB* root);
void Attach_AE_to_the_SA(Account_Element* AE_to_insert, Site_Account* SA);

Site_Account * Fill_the_SA_Form();
Account_Element * Fill_the_AE_Form();

Site_Account* Find_SA_Through_Number(DB * root, int select);
Account_Element* Find_AE_Through_Number(Site_Account * SA, int select);

int Delete_SA_From_DB(Site_Account * SA_to_delete, DB * root);
int Delete_AE_From_SA(Account_Element* AE_to_insert, Site_Account* SA);