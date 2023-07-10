// 定义回调函数
size_t write_callback_6pen(char* ptr, size_t size, size_t nmemb, std::string* userdata) {
	userdata->append(ptr, size * nmemb);
	return size * nmemb;
}

std::string Post6pen(std::string str) {
	string nullstr = "";

	CURL* curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl) {
		string dataHead = "{\n    \"prompt\": \"";
		string dataEnd = "\",\n    \"model_id\": 3,\n    \"height\": 512,\n    \"fill_prompt\": 0,\n    \"addition\": {\n        \"cfg_scale\": 7,\n        \"negative_prompt\": \"minim aliqua qui in sed\"\n    },\n    \"width\": 512\n}";
		string data2post = dataHead + String_To_UTF8(str) + dataEnd;
		const char* data = data2post.c_str();

		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(curl, CURLOPT_URL, "https://ston.6pen.art/release/open-task");
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_6pen);
		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "ys-api-key: ");// 你的apikey
		headers = curl_slist_append(headers, "User-Agent: Apifox/1.0.0 (https://apifox.com)");
		headers = curl_slist_append(headers, "Content-Type: application/json");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		//char data[] = "{\n    \"prompt\": \"层层叠叠的玫瑰花开在山坡上\",\n    \"model_id\": 3,\n    \"height\": 512,\n    \"fill_prompt\": 0,\n    \"addition\": {\n        \"cfg_scale\": 7,\n        \"negative_prompt\": \"minim aliqua qui in sed\"\n    },\n    \"width\": 512\n}";
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

		std::string response_data;
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
		res = curl_easy_perform(curl);

		int tar = response_data.find("\"id\":\"") + 6;
		int end = response_data.find("\",\"estimates");
		response_data = response_data.substr(tar, end - tar);
		response_data.erase(std::remove(response_data.begin(), response_data.end(), '\\'), response_data.end());
		cout << "\t[6Pen]" + response_data + "\n";

		curl_easy_cleanup(curl);
		return response_data;
	}
	curl_easy_cleanup(curl);
	return nullstr;
}

std::string Get6pen(std::string str) {
	string nullstr = "";

	CURL* curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl) {
		string urlHead = "https://ston.6pen.art/release/open-task?id=";
		str = urlHead + str;
		const char* url = str.c_str();
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_6pen);
		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "ys-api-key: ");// 你的apikey
		headers = curl_slist_append(headers, "User-Agent: Apifox/1.0.0 (https://apifox.com)");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		std::string response_data;
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
		res = curl_easy_perform(curl);

		curl_slist_free_all(headers);

		int tar = response_data.find("gen_img") + 10;
		int end = response_data.find("\",\"fail_reason");
		response_data = response_data.substr(tar, end - tar);
		response_data.erase(std::remove(response_data.begin(), response_data.end(), '\\'), response_data.end());
		cout << response_data;

		curl_easy_cleanup(curl);
		return response_data;
	}
	curl_easy_cleanup(curl);
	return nullstr;
}