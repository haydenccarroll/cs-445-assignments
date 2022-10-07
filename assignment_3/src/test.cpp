#include <filesystem>
#include <iostream>
#include <set>
#include <string>

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " program-name test-data-directory"
                  << std::endl;
        return EXIT_FAILURE;
    }

    std::filesystem::path program(argv[1]);
    std::filesystem::path testData(argv[2]);
    std::filesystem::path tempDir("./.tmpoutput");
    std::filesystem::path diffDir("./diff");
    std::set<std::string> files;

    system(std::string("rm -rf " + diffDir.string()).c_str());
    system(std::string("rm -rf " + tempDir.string()).c_str());
    system(std::string("mkdir " + diffDir.string()).c_str());
    system(std::string("mkdir " + tempDir.string()).c_str());

    for (const auto &dirent : std::filesystem::directory_iterator(testData)) {
        std::string path = dirent.path().string();
        std::string filename = dirent.path().filename().string();
        path = path.substr(0, path.find_last_of("."));
        filename = filename.substr(0, filename.find_last_of("."));

        if (files.find(path) == files.end()) {
            auto src_file = path + ".c-";
            auto out_file = path + ".out";

            if (!std::filesystem::exists(out_file)) {
                continue;
            }
            if (!std::filesystem::exists(src_file)) {
                continue;
            }

            auto program_output = tempDir.string() + "/" + filename;
            std::string run_program =
                program.string() + " -P " + src_file + " > " + program_output;
            system(run_program.c_str());

            std::string save_diff = "sdiff " + out_file + " " + program_output +
                                    " > " + diffDir.string() + "/" + filename +
                                    ".txt";
            system(save_diff.c_str());

            files.insert(path);
        }
    }

    system(std::string("rm -rf " + tempDir.string()).c_str());
}