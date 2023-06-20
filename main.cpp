#include <iostream>
#include <filesystem>
#include <string>

using namespace std;

void list_of_directory_files(filesystem::path& path) {
    //create a list of files in directory
    for (const auto& entry : filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            filesystem::path filePath = entry.path();
            //Check for extension of files
            string extension = filePath.extension().string();
            cout << "File: " << filePath << ", Extension: " << extension << endl;

            //Check if folder with extension for file was created
            filesystem::path extensionFolder = path / extension;
            //if not, create folder for extension
            if (!filesystem::exists(extensionFolder)) {
                filesystem::create_directory(extensionFolder);
                cout << "Created folder: " << extensionFolder << endl;
            }

            //Move file with X extension to folder which is deticated for extension
            filesystem::path destinationPath = extensionFolder / filePath.filename();
            if (!filesystem::exists(destinationPath)) {
                filesystem::rename(filePath, destinationPath);
                cout << "Moved file: " << filePath << " to: " << destinationPath << endl;
            }
            else {
                cout << "File already exist in the destination folder: " << destinationPath << endl;
            }
        }
    }
}

int main()
{
    cout << R"( 
 _______  __   __       _______         _______.  ______   .______     .___________. _______ .______      
|   ____||  | |  |     |   ____|       /       | /  __  \  |   _  \    |           ||   ____||   _  \     
|  |__   |  | |  |     |  |__         |   (----`|  |  |  | |  |_)  |   `---|  |----`|  |__   |  |_)  |    
|   __|  |  | |  |     |   __|         \   \    |  |  |  | |      /        |  |     |   __|  |      /     
|  |     |  | |  `----.|  |____    .----)   |   |  `--'  | |  |\  \----.   |  |     |  |____ |  |\  \----.
|__|     |__| |_______||_______|   |_______/     \______/  | _| `._____|   |__|     |_______|| _| `._____|
                                                                                                           by NIEDZKT)" << endl;
    int choice = 1;
    cout << "1. Select next directiory" << endl;
    cout << "2. Exit" << endl;
    cin >> choice;
    while (choice == 1) {
        string path_string;
        cout << "Paste your directory Path that you wanna sort: ";
        cin >> path_string;
        filesystem::path path = path_string;
        list_of_directory_files(path);
    }
    return 0;
}