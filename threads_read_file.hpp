#include <fstream>
#include <iostream>
#include <thread>
#include <shared_mutex>
#include <string>
std::string filename("C:\\Users\\sakabdel\\source\\repos\\SOCKNET_API\\www\\index.html");
class FileHandler {
	std::ifstream fileStream;
	std::string pathToFile;
	std::string buffer;
	unsigned int fileSize;
	bool isOpened = false;

public:
	FileHandler(std::string pathToFile) {
		this->pathToFile = pathToFile;
		this->fileStream.open(pathToFile);
		this->isOpened = true;
	}
	bool isOpen(void) {
		return this->fileStream.is_open();
	}
	std::string getLine() {
		buffer.clear();
		if (this->isOpen())
			std::getline(fileStream, buffer);
		return buffer;
	}
	void seek(unsigned int value) {
		this->fileStream.seekg(value);
	}

	std::ifstream getFileStream(void) {

	}
	void close() {
		this->fileStream.close();
	}

	bool eof(void) {
		return fileStream.eof();
	}
	void getFirst(void) {
		
	}
	~FileHandler() {
		//this->close();
	}
};

//struct mybuf : std::filebuf
//{
//	int underflow() {
//		std::cout << "Before underflow(): size of the get area is "
//			<< egptr() - eback() << " with "
//			<< egptr() - gptr() << " read positions available\n";
//		int rc = std::filebuf::underflow();
//		std::cout << "underflow() returns " << rc << ".\nAfter the call, "
//			<< "size of the get area is "
//			<< egptr() - eback() << " with "
//			<< egptr() - gptr() << " read positions available\n";
//		return rc;
//	}
//};

void foo(FileHandler* f) {
	std::string buf;
	while (!f->eof()) {
		std::cout << std::this_thread::get_id() << ": " << f->getLine() << std::endl;
	}
}

void bar(std::istream* stream) {
	std::cout << "Yerr...\n";
	std::string tmp;
	while (!stream->eof()) {
		tmp.clear();
		std::getline(*stream, tmp);
		//stream->getline(tmp.data(), 30);
		std::cout << tmp << std::endl;
	}
}

void Main() {
	//FileHandler* _file = new FileHandler("C:\\Users\\sakabdel\\source\\repos\\SOCKNET_API\\www\\index.html");
	////foo(*_file);
	//std::thread thr1(foo, _file), thr2(foo, _file);
	//thr1.join(); thr2.join();
	//_file->close();
	//delete _file;
	
	std::filebuf filebuf1;
	std::filebuf filebuf2;
	filebuf1.open(filename, std::ios_base::in);
	filebuf2.open(filename, std::ios_base::in);

	std::istream stream1(&filebuf1);
	bar(&stream1);
	stream1.clear();
	//filebuf1.close();

	std::istream stream2(&filebuf1);
	//stream2.seekg(0);
	bar(&stream2);
	filebuf2.close();

	/*std::ifstream fstream1;
	fstream1.open(filename);
	bar(&fstream1);
	fstream1.close();*/
	
	
	/*std::thread thr1(bar, &stream), thr2(bar, &stream);
	thr1.join(); thr2.join();*/

	
	return;
}