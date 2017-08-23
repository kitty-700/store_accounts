DB * Start_Import_Process();
int Is_File_Exists(FILE * fp);
DB * Import_File_and_Store_to_Memory(FILE * file_gate);
void Pass_Buffer_to_Proper_Position(char buffer[COMMON_LENGTH], DB * root);
int Judge_Operator(char byte);
void Decoding_Byte(char * byte);
int Get_File_Size(FILE * fp); 
void Store_to_Buffer(char buffer_to_store_byte[COMMON_LENGTH], const char byte_will_stored_to_buffer);
