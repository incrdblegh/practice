// This implementation of the Proxy pattern lacks additional functionality to check whether a file was
// actually modified, but for now it's not really needed to show what does the pattern do.

#include <iostream>
#include <memory>
#include <utility>

// The FileReader class defines a common interface for reading data from a file.
class FileReader {
  public:
    virtual ~FileReader() = default;

    // Reads data from a file and returns it as a string.
    virtual std::string readFile() = 0;
};

// The ConcreteFileReader class provides an implementation of the FileReader interface that reads data from a
// file on disk.
class ConcreteFileReader : public FileReader {
  public:
    // Reads data from a file on disk and returns it as a string.
    std::string readFile() override { return "some data from the file\n"; }
};

// The CachingFileReader class provides an implementation of the FileReader interface that caches the data
// read from a file to improve performance.
class CachingFileReader : public FileReader {
  public:
    // Constructs a CachingFileReader object that uses the specified FileReader
    // object to read data from a file.
    explicit CachingFileReader(std::shared_ptr<FileReader> fileReader)
        : m_fileReader{std::move(fileReader)} {}

    // Reads data from a file and returns it as a string. If the file has not been modified since the last
    // time it was read, the cached data is returned to improve performance.
    std::string readFile() override {
        if (m_isModified) {
            m_cache = m_fileReader->readFile();
            m_isModified = false;
        }
        return m_cache;
    }

  private:
    std::shared_ptr<FileReader> m_fileReader;
    std::string m_cache;
    bool m_isModified{true};
};

// The client function uses a FileReader object to read data from a file and print it to the standard output
// stream.
void client(const std::shared_ptr<FileReader>& fileReader) { std::cout << fileReader->readFile(); }

int main() {
    auto fileReader = std::make_shared<ConcreteFileReader>();
    auto proxy = std::make_shared<CachingFileReader>(fileReader);
    client(proxy);
}
