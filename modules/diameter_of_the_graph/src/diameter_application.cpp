// Copyright 2019 Savkin Yuriy

#include <cstring>
#include <string>
#include <stdexcept>
#include "include/diameter_application.h"

std::string DiameterApplication::operator()(int argc, const char** argv) {
    if (argc <= 1) {
        return HelpInfo();
    }

    matrix m;
    if (strcmp(argv[1], "init") == 0) {
        if (argc < 3)
            return "Incorrect usage of command \"init\"";
        int n;
        try {
            n = CastNumber(argv[2]);
        }
        catch(const std::runtime_error& re) {
            return "Error with argument " +
                std::to_string(2) + ": " + re.what();
        }
        m.resize(n);
        for (int i = 0; i < n; ++i) {
            m[i].assign(n, 0);
        }
    } else if (strcmp(argv[1], "help") == 0) {
        return HelpInfo();
    } else if (strcmp(argv[1], "add") == 0) {
        return "Incorrect usage of command \"add\"";
    } else if (strcmp(argv[1], "del") == 0) {
        return "Incorrect usage of command \"del\"";
    } else {
        return "Unknown command: " + std::string(argv[1]);
    }

    int i = 3;
    while (i < argc) {
        if (strcmp(argv[i], "add") == 0) {
            int x, y;
            if (i + 2 >= argc)
                return "Error: add has too few arguments";
            try {
                x = CastNumber(argv[i + 1]);
            }
            catch(const std::runtime_error& re) {
                return "Error with argument " +
                    std::to_string(i + 1) + ": " + re.what();
            }
            if (static_cast<unsigned>(x) >= m.size())
                return "Error with argument " +
                    std::to_string(i + 1) + ": out of range";
            try {
                y = CastNumber(argv[i + 2]);
            }
            catch(const std::runtime_error& re) {
                return "Error with argument " +
                    std::to_string(i + 2) + ": " + re.what();
            }
            if (static_cast<unsigned>(y) >= m.size())
                return "Error with argument " +
                    std::to_string(i + 2) + ": out of range";
            m[x][y] = 1;
            m[y][x] = 1;
            i += 3;
        } else if (strcmp(argv[i], "del") == 0) {
            int x, y;
            if (i + 2 >= argc)
                return "Error: del has too few arguments";
            try {
                x = CastNumber(argv[i + 1]);
            }
            catch(const std::runtime_error& re) {
                return "Error with argument " +
                    std::to_string(i + 1) + ": " + re.what();
            }
            if (static_cast<unsigned>(x) >= m.size())
                return "Error with argument " +
                    std::to_string(i + 1) + ": out of range";
            try {
                y = CastNumber(argv[i + 2]);
            }
            catch(const std::runtime_error& re) {
                return "Error with argument " +
                    std::to_string(i + 2) + ": " + re.what();
            }
            if (static_cast<unsigned>(y) >= m.size())
                return "Error with argument " +
                    std::to_string(i + 2) + ": out of range";
            m[x][y] = 0;
            m[y][x] = 0;
            i += 3;
        } else if (strcmp(argv[i], "help") == 0) {
            return "Incorrect usage of command \"help\"";
        } else if (strcmp(argv[i], "init") == 0) {
            return "Incorrect usage of command \"init\"";
        } else {
            return "Unknown command: " + std::string(argv[i]);
        }
    }

    Graph gr(std::move(m), static_cast<int>(m.size()));
    int diam = gr.DiameterOfGraph();
    if (diam == 1073741823)
        return "Error: disconnected graph";
    if (diam == -2)
        return "Error: graph has no vertexes";
    return std::to_string(diam);
}

std::string DiameterApplication::HelpInfo() {
    return "Commands:\n"
           "init <number> - sets number of vertexes.\n"
           "This command must be the first and is to be used once\n"
           "add <x> <y> - adds edges (x, y) and (y, x) to graph.\n"
           "del <x> <y> - deletes edges (x, y) and (y, x) from graph.\n"
           "help - prints helping information";
}

int DiameterApplication::CastNumber(const char* num) {
    std::string max_str("50");
    unsigned len = 0;
    while (num[len] != '\0') {
        if (!isdigit(num[len]))
            throw std::runtime_error("not a number");
        ++len;
    }
    if (len > max_str.size()) {
        throw std::runtime_error("too big number");
    } else if (len == max_str.size()) {
        for (unsigned i = 0; i < len; ++i) {
            if (num[i] < max_str[i]) {
                break;
            } else if (num[i] > max_str[i]) {
                throw std::runtime_error("too big number");
            }
        }
    }
    return atoi(num);
}
