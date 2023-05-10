#include <iostream>
#include <string>
#include <vector>
//перекодовує відео
#include "VideoConverter.h"
//бібліотека яка дозволяє працювати з API YouTube
#include "YouTubeAPI.h"

using namespace std;

//фасад, який дозволяє завантажити відео на YouTube
class YouTubeUploader {
public:
    YouTubeUploader(const string& apiKey) {
        api = new YouTubeAPI(apiKey);
        converter = new VideoConverter();
    }

    ~YouTubeUploader() {
        delete api;
        delete converter;
    }

    //завантаження відео на YouTube
    bool uploadVideo(const string& filePath) {
        //конвертація відео в формат, який підтримується YouTube
        string convertedFilePath = converter->convert(filePath);

        //завантаження відео на YouTube
        bool success = api->uploadVideo(convertedFilePath);

        //видалення тимчасового файла
        remove(convertedFilePath.c_str());

        return success;
    }

private:
    YouTubeAPI* api;
    VideoConverter* converter;
};

//використання фасаду для завантаження відео на YouTube
int main() {
    string apiKey = "api_key";
    string filePath = "video.mp4";

    YouTubeUploader uploader(apiKey);
    bool success = uploader.uploadVideo(filePath);

    if (success) {
        cout << "Відео успішно завантажено" << endl;
    } else {
        cout << "Помилка завантаження відео" << endl;
    }

    return 0;
}