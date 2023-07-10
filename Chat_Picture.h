#define max_picture_count 30

using namespace std;

class chat_picture {
public:
	std::string String;
	const wchar_t* Path;
	void chat_picture_init(const char* str, const wchar_t* path) {
		String = str;
		Path = path;
	}
};

class chat_picture_list {
public:
	chat_picture cp[max_picture_count];
	chat_picture_list() {
		cp[0].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\001.png");// 填写你自己的图片和地址
		cp[1].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\002.png");
		cp[2].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\003.png");
		cp[3].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\004.png");
		cp[4].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\005.png");
		cp[5].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\006.png");
		cp[6].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\007.png");
		cp[7].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\008.png");
		cp[8].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\009.png");
		cp[9].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\010.png");
		cp[10].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\011.png");
		cp[11].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\012.png");
		cp[12].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\013.png");
		cp[13].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\014.png");
		cp[14].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\015.png");
		cp[15].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\016.png");
		cp[16].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\017.png");
		cp[17].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\018.png");
		cp[18].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\019.png");
		cp[19].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\020.png");
		cp[20].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\021.png");
		cp[21].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\022.png");
		cp[22].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\023.png");
		cp[23].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\024.png");
		cp[24].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\025.png");
		cp[25].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\026.png");
		cp[26].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\027.png");
		cp[27].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\028.png");
		cp[28].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\029.png");
		cp[29].chat_picture_init("藤原 https://www.pixiv.net/users/27517", L"D:\\Pictures\\030.png");
	}
	chat_picture* Rand() {
		int tar = rand() % max_picture_count;
		return &cp[tar];
	}
};

chat_picture_list C_P_L;