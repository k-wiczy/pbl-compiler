#include "gtest/gtest.h"
#include "lexer/lexer.h"

TEST(Lexer, basic) {
    Lexer lexer ("basic.pbl");
    auto tokens = lexer.GetTokens();
    for (auto token : tokens) {
        std::cout << token.Info() << std::endl;
    }

    EXPECT_EQ(tokens[0].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[0].GetValue(), "pipe");

    EXPECT_EQ(tokens[1].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[1].GetValue(), "main");

    EXPECT_EQ(tokens[2].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[2].GetValue(), "(");

    EXPECT_EQ(tokens[3].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[3].GetValue(), "input");

    EXPECT_EQ(tokens[4].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[4].GetValue(), "bit");

    EXPECT_EQ(tokens[5].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[5].GetValue(), "<");

    EXPECT_EQ(tokens[6].GetType(), Lexer::Token::TokenType::TOKEN_NUMERIC_LITERAL);
    EXPECT_EQ(tokens[6].GetValue(), "32");

    EXPECT_EQ(tokens[7].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[7].GetValue(), ">");

    EXPECT_EQ(tokens[8].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[8].GetValue(), "rx");

    EXPECT_EQ(tokens[9].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[9].GetValue(), ",");

    EXPECT_EQ(tokens[10].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[10].GetValue(), "output");

    EXPECT_EQ(tokens[11].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[11].GetValue(), "bit");

    EXPECT_EQ(tokens[12].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[12].GetValue(), "<");

    EXPECT_EQ(tokens[13].GetType(), Lexer::Token::TokenType::TOKEN_NUMERIC_LITERAL);
    EXPECT_EQ(tokens[13].GetValue(), "32");

    EXPECT_EQ(tokens[14].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[14].GetValue(), ">");

    EXPECT_EQ(tokens[15].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[15].GetValue(), "tx");

    EXPECT_EQ(tokens[16].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[16].GetValue(), ")");

    EXPECT_EQ(tokens[17].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[17].GetValue(), "{");

    EXPECT_EQ(tokens[18].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[18].GetValue(), "tx");

    EXPECT_EQ(tokens[19].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[19].GetValue(), "=");

    EXPECT_EQ(tokens[20].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[20].GetValue(), "rx");

    EXPECT_EQ(tokens[21].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[21].GetValue(), ";");

    EXPECT_EQ(tokens[22].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[22].GetValue(), "}");
}

TEST(Lexer, comments) {
    Lexer lexer ("comments.pbl");
    auto tokens = lexer.GetTokens();
    for (auto token : tokens) {
        std::cout << token.Info() << std::endl;
    }

    EXPECT_EQ(tokens[0].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[0].GetValue(), "bit");

    EXPECT_EQ(tokens[1].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[1].GetValue(), "dbg");

    EXPECT_EQ(tokens[2].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[2].GetValue(), ";");

    EXPECT_EQ(tokens[3].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[3].GetValue(), "pipe");

    EXPECT_EQ(tokens[4].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[4].GetValue(), "main");

    EXPECT_EQ(tokens[5].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[5].GetValue(), "(");

    EXPECT_EQ(tokens[6].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[6].GetValue(), ")");

    EXPECT_EQ(tokens[7].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[7].GetValue(), ";");
}

TEST(Lexer, numeric) {
    Lexer lexer ("numeric.pbl");
    auto tokens = lexer.GetTokens();
    for (auto token : tokens) {
        std::cout << token.Info() << std::endl;
    }

    EXPECT_EQ(tokens[0].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[0].GetValue(), "int");

    EXPECT_EQ(tokens[1].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[1].GetValue(), "a");

    EXPECT_EQ(tokens[2].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[2].GetValue(), "=");

    EXPECT_EQ(tokens[3].GetType(), Lexer::Token::TokenType::TOKEN_NUMERIC_LITERAL);
    EXPECT_EQ(tokens[3].GetValue(), "23");

    EXPECT_EQ(tokens[4].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[4].GetValue(), ";");

    EXPECT_EQ(tokens[5].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[5].GetValue(), "fix");

    EXPECT_EQ(tokens[6].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[6].GetValue(), "<");

    EXPECT_EQ(tokens[7].GetType(), Lexer::Token::TokenType::TOKEN_NUMERIC_LITERAL);
    EXPECT_EQ(tokens[7].GetValue(), "32");

    EXPECT_EQ(tokens[8].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[8].GetValue(), ",");

    EXPECT_EQ(tokens[9].GetType(), Lexer::Token::TokenType::TOKEN_NUMERIC_LITERAL);
    EXPECT_EQ(tokens[9].GetValue(), "16");

    EXPECT_EQ(tokens[10].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[10].GetValue(), ">");

    EXPECT_EQ(tokens[11].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[11].GetValue(), "b");

    EXPECT_EQ(tokens[12].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[12].GetValue(), "=");

    EXPECT_EQ(tokens[13].GetType(), Lexer::Token::TokenType::TOKEN_NUMERIC_LITERAL);
    EXPECT_EQ(tokens[13].GetValue(), "22.33");

    EXPECT_EQ(tokens[14].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[14].GetValue(), ";");

    EXPECT_EQ(tokens[15].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[15].GetValue(), "bit");

    EXPECT_EQ(tokens[16].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[16].GetValue(), "<");

    EXPECT_EQ(tokens[17].GetType(), Lexer::Token::TokenType::TOKEN_NUMERIC_LITERAL);
    EXPECT_EQ(tokens[17].GetValue(), "32");

    EXPECT_EQ(tokens[18].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[18].GetValue(), ">");

    EXPECT_EQ(tokens[19].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[19].GetValue(), "c");

    EXPECT_EQ(tokens[20].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[20].GetValue(), "=");

    EXPECT_EQ(tokens[21].GetType(), Lexer::Token::TokenType::TOKEN_NUMERIC_LITERAL);
    EXPECT_EQ(tokens[21].GetValue(), "0xDEADBEEF");

    EXPECT_EQ(tokens[22].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[22].GetValue(), ";");

    EXPECT_EQ(tokens[23].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[23].GetValue(), "bit");

    EXPECT_EQ(tokens[24].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[24].GetValue(), "<");

    EXPECT_EQ(tokens[25].GetType(), Lexer::Token::TokenType::TOKEN_NUMERIC_LITERAL);
    EXPECT_EQ(tokens[25].GetValue(), "4");

    EXPECT_EQ(tokens[26].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[26].GetValue(), ">");

    EXPECT_EQ(tokens[27].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[27].GetValue(), "d");

    EXPECT_EQ(tokens[28].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[28].GetValue(), "=");

    EXPECT_EQ(tokens[29].GetType(), Lexer::Token::TokenType::TOKEN_NUMERIC_LITERAL);
    EXPECT_EQ(tokens[29].GetValue(), "0b1010");

    EXPECT_EQ(tokens[30].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[30].GetValue(), ";");

    EXPECT_EQ(tokens[31].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[31].GetValue(), "int");

    EXPECT_EQ(tokens[32].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[32].GetValue(), "e");

    EXPECT_EQ(tokens[33].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[33].GetValue(), "=");

    EXPECT_EQ(tokens[34].GetType(), Lexer::Token::TokenType::TOKEN_NUMERIC_LITERAL);
    EXPECT_EQ(tokens[34].GetValue(), "0d123");

    EXPECT_EQ(tokens[35].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[35].GetValue(), ";");

    EXPECT_EQ(tokens[36].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[36].GetValue(), "int");

    EXPECT_EQ(tokens[37].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[37].GetValue(), "f");

    EXPECT_EQ(tokens[38].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[38].GetValue(), "=");

    EXPECT_EQ(tokens[39].GetType(), Lexer::Token::TokenType::TOKEN_NUMERIC_LITERAL);
    EXPECT_EQ(tokens[39].GetValue(), "-33");

    EXPECT_EQ(tokens[40].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[40].GetValue(), ";");
}

TEST(Lexer, string) {
    Lexer lexer ("string.pbl");
    auto tokens = lexer.GetTokens();
    for (auto token : tokens) {
        std::cout << token.Info() << std::endl;
    }

    EXPECT_EQ(tokens[0].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[0].GetValue(), "string");

    EXPECT_EQ(tokens[1].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[1].GetValue(), "test");

    EXPECT_EQ(tokens[2].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[2].GetValue(), "=");

    EXPECT_EQ(tokens[3].GetType(), Lexer::Token::TokenType::TOKEN_STRING_LITERAL);
    EXPECT_EQ(tokens[3].GetValue(), "This is a test!");

    EXPECT_EQ(tokens[4].GetType(), Lexer::Token::TokenType::TOKEN_OPERATOR);
    EXPECT_EQ(tokens[4].GetValue(), ";");
}

TEST(Lexer, preprocessor) {
    Lexer lexer ("preprocessor.pbl");
    auto tokens = lexer.GetTokens();
    for (auto token : tokens) {
        std::cout << token.Info() << std::endl;
    }

    EXPECT_EQ(tokens[0].GetType(), Lexer::Token::TokenType::TOKEN_PREPROCESSOR);
    EXPECT_EQ(tokens[0].GetValue(), "include");

    EXPECT_EQ(tokens[1].GetType(), Lexer::Token::TokenType::TOKEN_STRING_LITERAL);
    EXPECT_EQ(tokens[1].GetValue(), "file.pbl");

    EXPECT_EQ(tokens[2].GetType(), Lexer::Token::TokenType::TOKEN_PREPROCESSOR);
    EXPECT_EQ(tokens[2].GetValue(), "define");

    EXPECT_EQ(tokens[3].GetType(), Lexer::Token::TokenType::TOKEN_SYMBOL);
    EXPECT_EQ(tokens[3].GetValue(), "TAPS");

    EXPECT_EQ(tokens[4].GetType(), Lexer::Token::TokenType::TOKEN_NUMERIC_LITERAL);
    EXPECT_EQ(tokens[4].GetValue(), "10");
}

int main(int argc, char ** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}