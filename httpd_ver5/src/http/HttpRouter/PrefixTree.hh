//
// Created by Pawn on 2020/7/23.
//

#ifndef HTTPROUTER_PREFIXTREE_H
#define HTTPROUTER_PREFIXTREE_H


#include <string>
#include <algorithm>

#include "HttpRouterError.hh"
#include "HttpHandler.hh"
// 经过一点点优化的前缀树

// 当前先不考虑优化和静态路由的问题

const int K = 128;

namespace singsing{
enum class PrefixTreeNodeType : uint8_t
{
    InvalidNode = 0,
    RootNode,
    CommonNode,
    WildcardNode ,
};


#

class PrefixTree
{
    using FuncType = HttpHandler;
    using ResultType = std::pair<bool, FuncType >;

private:
    template <int dict_size>
    class PrefixTreeNode
    {
    public:
        /** Initialize your data structure here. */
        PrefixTreeNode() {}

        ~PrefixTreeNode()
        {
            for (int i = 0; i < dict_size; i++)
            {
                if (next_[i] == nullptr) continue;
                delete(next_[i]);
                next_[i] = nullptr;
            }
        }

        void insert(const std::string& word, const FuncType &t, PrefixTreeNodeType type)
        {
            PrefixTreeNode *node = this;
            for (auto c : word)
            {
                if (node->next_[c] == nullptr)
                {
                    node->next_[c] = new PrefixTreeNode<dict_size>();
                }
                node = node->next_[c];
            }
            node->is_string_ = true;
            node->handler_ = t;
            node->type_ = type;
        }
        /** Inserts a word into the trie. */
        void insert(const std::string& word, FuncType && t, PrefixTreeNodeType type)
        {
            PrefixTreeNode *node = this;
            for (auto c : word)
            {
                if (node->next_[c] == nullptr)
                {
                    node->next_[c] = new PrefixTreeNode<dict_size>();
                    node->handler_ = std::move(t);
                    node->type_ = type;
                }
                node = node->next_[c];
            }
            node->is_string_ = true;
        }

        /** Returns if the word is in the trie. */
        ResultType search(const std::string& word)
        {
            PrefixTreeNode *node = this;
            for (auto c : word)
            {
                if (node->next_[c] == nullptr) return {false, FuncType {}};
                node = node->next_[c];
            }
            if(node->is_string_)
                return {true, handler_} ;
            else
                return {false, FuncType {}};
        }

        /** Returns if there is any word in the trie that starts with the given prefix. */
        ResultType startsWith(const std::string& prefix)
        {
            PrefixTreeNode *node = this;
            for (auto c : prefix)
            {
                if (node->next_[c] == nullptr) return {false, FuncType {}};
                node = node->next_[c];
            }
            return {true, handler_};
        }

        PrefixTreeNodeType type_{PrefixTreeNodeType::InvalidNode};
        bool is_string_ = false;
        FuncType handler_;
        PrefixTreeNode* next_[dict_size] = {nullptr};
    };
public:
    PrefixTree()
    {

    }



    void add_route(const std::string& word, const FuncType &t)
    {

        if(!root)
        {
            root = new PrefixTreeNode<K> ();
        }

        auto res_pair = has_star(word);
        if(res_pair.first)
        {
            auto prefix = res_pair.second;
            root->insert(prefix, t, PrefixTreeNodeType::WildcardNode);
        }else{
            root->insert(word, t, PrefixTreeNodeType::CommonNode);
        }
    }
    FuncType search(const std::string& str)
    {
        if(!root)
            throw HttpRouter_NoHandler("没有设置任何路由");


        // 查找的时候要先找普通节点，如果找不到再去找wildcard节点
        FuncType handler;

        auto node = root;
        bool has_handler = false;
        bool is_for_end = true;
        for (auto c : str)
        {
            if (node->next_[ c-0 ] == nullptr){
                // 尝试去看是否有wildcard节点配置好的路由
                is_for_end = false;
                break;
            }
            node = node->next_[c-0];
            if(PrefixTreeNodeType::WildcardNode == node->type_)
            {
                has_handler = true;
                handler = node->handler_;
            }
        }
        // is_for_end 为false代表循环没有走完
        if(is_for_end && PrefixTreeNodeType::CommonNode == node->type_)
        {
            has_handler = true;
            handler = node->handler_;
        }
        if(!has_handler)
            throw HttpRouter_NoHandler("没有匹配到任何路由");
        return handler;
    }

private:
    // 是否有*号
    std::pair<bool, std::string> has_star(const std::string& word)
    {
        for(int i = 0; i < word.size(); i++)
        {
            if(word[i] == '*')
            {
                return {true, word.substr(0, i)};
            }
        }
        return {false, word};
    }

private:
    PrefixTreeNode<K> *root{nullptr};
};


}
#endif //HTTPROUTER_PREFIXTREE_H

