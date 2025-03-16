#include "TMDB.hpp"


string ParserJson(const string&& response) {
    Parser parser;
    Poco::Dynamic::Var result = parser.parse(response);
    Object::Ptr jsonObject = result.extract<Object::Ptr>();
    Array::Ptr jsonArray = jsonObject->getArray("results");
    string data;
    for (size_t i = 0; i < jsonArray->size(); ++i) {
        jsonObject = jsonArray->getObject(i);
        data += fmt::format(fg(fmt::color::bisque), "title: ")
        + fmt::format(fg(fmt::color::dark_cyan) | fmt::emphasis::bold, "{}", jsonObject->getValue<string>("title") + '\n')
        + fmt::format(fg(fmt::color::bisque), "release_date: ")
        + fmt::format(fg(fmt::color::olive_drab) | fmt::emphasis::bold, "{}", jsonObject->getValue<string>("release_date") + '\n')
        + fmt::format(fg(fmt::color::bisque), "popularity: ")
        + fmt::format(fg(fmt::color::dark_gray) | fmt::emphasis::bold, "{}", jsonObject->getValue<string>("popularity") + '\n')
        + fmt::format(fg(fmt::color::bisque), "vote_count: ")
        + fmt::format(fg(fmt::color::purple) | fmt::emphasis::bold, "{}", jsonObject->getValue<string>("vote_count") + '\n')
        + fmt::format(fg(fmt::color::red) | fmt::emphasis::bold, "{}", (i != jsonArray->size() - 1 ? "--------------------------------------\n" : ""));
    }
    return data;
}

string GetResponse(const char* type) {
    string url = "https://api.themoviedb.org/3/movie/";
    if (strcmp(type, "playing") == 0) url.append("now_playing");
    else if (strcmp(type, "popular") == 0) url.append(type);
    else if (strcmp(type, "top") == 0) url.append("top_rated");
    else if (strcmp(type, "upcoming") == 0) url.append(type);
    else throw logic_error("look README file.");
    url.append("?language=en-US&page=1");
    URI uri(url);
    HTTPSClientSession session(uri.getHost(), uri.getPort());
    HTTPRequest request(HTTPRequest::HTTP_GET, uri.getPathAndQuery(), HTTPRequest::HTTP_1_1);
    request.set("Authorization", "Bearer eyJhbGciOiJIUzI1NiJ9.eyJhdWQiOiI5NGY3OTZmYTZmMTgwNGJiNGY1YWUxZjNhNTgzZThiMCIsIm5iZiI6MTc0MjA0MjUxMC44MTksInN1YiI6IjY3ZDU3NThlMzE2NzhjYzNmODAxMjljOCIsInNjb3BlcyI6WyJhcGlfcmVhZCJdLCJ2ZXJzaW9uIjoxfQ.LhJ5f6Rfcjg7eDLEJV5lFhkvpISqQDBes4GI4CpRL8M");
    request.set("user-agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/134.0.0.0 Safari/537.36");
    session.sendRequest(request);
    HTTPResponse response;
    istream &is = session.receiveResponse(response);
    string resposneStr;
    StreamCopier::copyToString(is, resposneStr);
    return ParserJson(move(resposneStr));
}