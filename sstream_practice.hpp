#include <sstream>
#include <iostream>
#include <map>
using namespace std;

string getRequest(
	"GET /21f06cea3ae9e8b11bd49ec6cafa0ee09fa6dae2/styles.91ccdfabaac628436cb9.bundle.js"
	"?Policy=eyJTdGF0ZW1lbnQiOlt7IlJlc291cmNlIjoiaHR0cHM6Ly9kbTB3aXdvYjg5cGdpLmNsb3VkZnJvbnQubmV0LyoiL"
	"CJDb25kaXRpb24iOnsiRGF0ZUxlc3NUaGFuIjp7IkFXUzpFcG9jaFRpbWUiOjE2NzU5NTI1NTh9fX1dfQ__&Signature=ddw8"
	"CHyN0hnUTVarl8HeOk7VtG2CAIenx9rd2lM8W4IV4tAC679Jhi4wY-mjHGcGgr~3AyF8fR146czQO6YiYZ6hTHtuTyx9O0yvXi"
	"GgKcgbjvM3ZHZFsXd3mq8umXDWI1FOzVa66prvNYdKqhxXDKF8CyZtGvgb-gimsHSJnOhyyHkMW3vyExzn-zlJ7x0YWapK2t59"
	"zyN8LEvLhKVI3ZyLWCnlrNXPJmE6C3Zl3CodsVN4CTkLa7zpVqCVgjHgifBOD20XwE-DcWu-rzmcZvARfmgfZ~FwH1hcknPJ-6"
	"eUKVWjWVBew4MuOyd86u711-ZvheCkYeNdfrx7~QfJxA__&Key-Pair-Id=APKAIAMK7WSX2CNI3IIQ HTTP/2\n\r"
	"Host: dm0wiwob89pgi.cloudfront.net\n\r"
	"User - Agent: Mozilla / 5.0 (Windows NT 10.0; Win64; x64; rv:102.0) Gecko / 20100101 Firefox / 102.0\n\r"
	"Accept: */*\n\r"
	"Accept-Language: en-US,en;q=0.5\n\r"
	"Accept-Encoding: gzip, deflate, br\n\r"
	"Connection: keep-alive\n\r"
	"Referer: https://t.corp.amazon.com/\n\r"
	"Sec-Fetch-Dest: script\n\r"
	"Sec-Fetch-Mode: no-cors\n\r"
	"Sec-Fetch-Site: cross-site\n\r"
	"TE: trailers\n\r\n\r");

class HttpRequest {
	string method;
	string url;
	string version;
	map<string, string> headers;
public:
	HttpRequest(stringstream& stream) {
		string nada;
		stream >> method >> url >> version;
		getline(stream, nada);//gets the following \n char;
		string key, value;
		while (true) {
			getline(stream, key, ':');
			getline(stream, value);
			if (stream.eof())
				break;
			key.erase(0, 1); // removes \r at the beginning;
			value.erase(0, 1); //removes space at the beginning.
			headers[key] = value;
			cout << key << " --> " << value << endl;
		}
	} 
	string getMethod(void) { return method; }
	string getUrl(void) { return url; }
	string getVersion(void) { return version; }
	string getHeader(string header) {
		if (auto member = headers.find(header); member != headers.end())
			return member->second;
		else
			NULL;
		
	}
};

void Main(void) {
	stringstream ss;
	ss << getRequest;
	HttpRequest httpRequest(ss);
	string host = httpRequest.getHeader("Host");
	cout << "host value" <<  host << endl;
	//cout << httpRequest.getMethod() << ' ' << httpRequest.getUrl() << ' ' << httpRequest.getVersion() << ' ' << endl;
}