//컴파일 시 파일 이름 관련
#define LOAD_FILE_NAME \
"123.zip"
#define EXPORT_FILE_NAME \
"123.zip"
/*배포용 더미 이름으로 쓸만한 것들
"[tvN] 문제적 남자.E126.170820.720p NEXT.mp4.torrent"
"베이워치 SOS 해상 구조대 Baywatch.2017.UNRATED.1080p.BluRay.x264.TrueHD.7.1.Atmos FGT.torrent"
"자격지심 (Feat. 은하 of 여자친구).mp3"
"충돌  아랍의 봄  그 이후 Clash  2016  720p BRRip 850MB - MkvCage.torrent"
"틸 위 미트 어게인 (Till We Meet Again, 2016) bluray SRT (자막).zip"
*/
//컴파일 시 설정 관련
#define TEST_MODULE FALSE

#define ACTIVE_ENCODING FALSE
#define ACTIVE_DECODING FALSE
#define GENERATE_JUNK_BYTE TRUE	//모르는 사람이 파일뚜껑을 열었을 때 해석하기 어렵도록.

#define SHOW_ENCODING_PROCESS FALSE	//EXPORT_DEBUG 와 겹치는 느낌
#define SHOW_DECODING_PROCESS FALSE//IMPORT_DEBUG 와 겹치는 느낌
#define IMPORT_DEBUG FALSE
#define EXPORT_DEBUG FALSE

#define MAX_OF_CREATE_JUNK_BYTES 300000
#define MIN_OF_CREATE_JUNK_BYTES 300000
#define IMPORT_DELAY_SEC 1
#define EXPORT_DELAY_SEC 1
////////////////////////////////////
#define DO_LOGIN_PROCESS FALSE
#define PASS_CHAR1 'k'

#define USE_PASSWORD_IN_LOGIN FALSE
#define THEN_PASSWORD "itty"

#define HELP_MESSAGE "스발스발"

#define SHOW_SOURCE TRUE