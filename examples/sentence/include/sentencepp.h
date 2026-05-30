#ifndef SENTENCEPP_H
#define SENTENCEPP_H
/**
* @file sentencepp.h
* @date 2026-05-22
* @author NightZero91
* @brief 自然语言句子类(适合做事件，及触发器)
* @note 使用模板元编程
*/
#include <functional>
namespace tlz
{
    /**
    *@brief 句子基本类型
    */
    enum class SentenceStructure
    {
        SUBJECT_PREDICATE,              //主谓
        SUBJECT_PREDICATE_OBJECT,       //主谓宾
        SUBJECT_PREDICATE_COMPLEMENT    //主系表
    };

    namespace sentence 
    {
        /**
        *@brief 名词类
        *@tparam Name：是类型名，可以存对象，名词存有的东西叫做[名词的意义]
        */
        template <class Name>
        class Noun
        {
        protected:
            Name name;
        public:
            /**
            *@brief 构造一个名词
            *@param _name：名词含有的意义(值)
            */
            Noun(const Name& _name) : name(_name){}
            Name get() const noexcept
            {
                return name;
            }
        };
        /**
        *@brief 主语类和谓语类
        */
        template <class Name>
        class Subject : public Noun<Name>
        {
        public:
            Subject(const Name& _name) : Noun<Name>(_name){}
        };

        template <class Name>
        class Object : public Noun<Name>
        {
        public:
            Object(const Name& _name) : Noun<Name>(_name){}
        };
        /**
        *@brief 一个用来占位的空类型
        */
        struct nullname {};
        /**
        *@brief 句子执行所返回的句子包
        */
        //主谓句子包
        //SubjectName：主语类型
        template<class SubjectName>
        struct SentencePackSV
        {
            //谁是主语-who
            Subject<SubjectName>who;
            /**
            *@brief 之后执行什么句子(可选)
            *@tparam SentenceType：句子， Args：句子执行参数
            *@param sentence：句子
            *@param args：句子执行参数
            *@note 可以链式调用
            */
            template<class SentenceType, class ...Args>
            auto& then(SentenceType& sentence, Args ...args)
            {
                sentence.say(args...);
                return *this;
            }
            /**
            *@brief 如果条件满足，之后执行什么句子(可选)
            *@tparam SentenceType：句子， Args：句子执行参数
            *@param sentence：句子
            *@param args：句子执行参数
            *@param condition：什么条件下执行
            *@note 可以链式调用
            */
            template<class SentenceType, class ...Args>
            auto& if_then(bool condition, SentenceType& sentence, Args ...args)
            {
                if (condition) sentence.say(args...);
                return *this;
            }
        };
        //主谓宾句子包
        //SubjectName：主语类型
        //ObjectName：宾语类型
        template<class SubjectName, class ObjectName>
        struct SentencePackSVO
        {
            //谁是主语-who
            Subject<SubjectName>who;
            //谁是宾语-obj
            Object<ObjectName>obj;
            /**
            *@brief 之后执行什么句子(可选)
            *@tparam SentenceType：句子， Args：句子执行参数
            *@param sentence：句子
            *@param args：句子执行参数
            *@note 可以链式调用
            */
            template<class SentenceType, class ...Args>
            auto& then(SentenceType& sentence, Args ...args)
            {
                sentence.say(args...);
                return *this;
            }
            /**
            *@brief 如果条件满足，之后执行什么句子(可选)
            *@tparam SentenceType：句子， Args：句子执行参数
            *@param sentence：句子
            *@param args：句子执行参数
            *@param condition：什么条件下执行
            *@note 可以链式调用
            */
            template<class SentenceType, class ...Args>
            auto& if_then(bool condition, SentenceType& sentence, Args ...args)
            {
                if (condition) sentence.say(args...);
                return *this;
            }
        };
        //主系表句子包
        //SubjectName：主语类型
        //PredicateName：表语类型
        template<class SubjectName, class PredicateName>
        struct SentencePackSVP
        {
            //谁是主语-who
            Subject<SubjectName>who;
            //表语-predicate
            PredicateName predicate;
            /**
            *@brief 之后执行什么句子(可选)
            *@tparam SentenceType：句子， Args：句子执行参数
            *@param sentence：句子
            *@param args：句子执行参数
            *@note 可以链式调用
            */
            template<class SentenceType, class ...Args>
            auto& then(SentenceType& sentence, Args ...args)
            {
                sentence.say(args...);
                return *this;
            }
            /**
            *@brief 如果条件满足，之后执行什么句子(可选)
            *@tparam SentenceType：句子， Args：句子执行参数
            *@param sentence：句子
            *@param args：句子执行参数
            *@param condition：什么条件下执行
            *@note 可以链式调用
            */
            template<class SentenceType, class ...Args>
            auto& if_then(bool condition, SentenceType& sentence, Args ...args)
            {
                if (condition) sentence.say(args...);
                return *this;
            }
        };
        /**
        *@brief 一个句子的模板类
        *@tparam SentenceStructure：句子结构
        *@tparam ReturnValue：句子返回值（一般被忽略）
        *@tparam SubjectName：主语类型
        *@tparam ObjectName：宾语类型
        *@tparam PredicateName：表语类型
        *@tparam Args：执行句子所需要的参数
        *@note 不用填的地方用nullname占用
        */
        template<SentenceStructure SS, class ReturnValue, class SubjectName, class ObjectName, class PredicateName, class ...Args>
        class Sentence{};

        //主谓句子
        template<class ReturnValue, class SubjectName, class ObjectName, class PredicateName, class ...Args>
        class Sentence<SentenceStructure::SUBJECT_PREDICATE, ReturnValue, SubjectName, ObjectName, PredicateName, Args...>
        {
        private:
            Subject<SubjectName> subject;
            std::function<ReturnValue(Args...)> predicate_verb;
        public:
            Sentence() = delete;
            /**
            *@brief 构造主谓句子
            *@param sub：主语
            *@param predicate：谓语动词
            */
            Sentence(const Subject<SubjectName>& sub, const std::function<ReturnValue(Args...)>& predicate):
            subject(sub), predicate_verb(predicate){}
            /**
            *@brief 说句子(执行句子)
            *@param args：执行句子需要的参数
            *@return 返回句子包
            */
            SentencePackSV<SubjectName> say(Args ...args)
            {
                predicate_verb(args...);
                return SentencePackSV<SubjectName>{ subject };
            }
            /**
            *@brief 获取主语
            */
            Subject<SubjectName> get_subject() const noexcept
            {
                return subject;
            }
        };

        //主谓宾句子
        template<class ReturnValue, class SubjectName, class ObjectName, class PredicateName, class ...Args>
        class Sentence<SentenceStructure::SUBJECT_PREDICATE_OBJECT, ReturnValue, SubjectName, ObjectName, PredicateName, Args...>
        {
        private:
            Subject<SubjectName> subject;
            Object<ObjectName>object;
            std::function<ReturnValue(Object<ObjectName>& ,Args...)> predicate_verb;
        public:
            Sentence() = delete;
            /**
            *@brief 构造主谓句子
            *@param sub：主语
            *@param predicate：谓语动词
            *@param obj：宾语
            */
            Sentence(const Subject<SubjectName> &sub, const Object<ObjectName> &obj, const std::function<ReturnValue(Object<ObjectName>&, Args...)> &predicate):
            subject(sub), predicate_verb(predicate), object(obj){}
            /**
            *@brief 说句子(执行句子)
            *@param args：执行句子需要的参数
            *@return 返回句子包
            */
            SentencePackSVO<SubjectName, ObjectName> say(Args ...args)
            {
                predicate_verb(object, args...);
                return SentencePackSVO<SubjectName, ObjectName>{ subject, object };
            }
            /**
            *@brief 获取主语
            */
            Subject<SubjectName> get_subject() const noexcept
            {
                return subject;
            }
            /**
            *@brief 获取宾语
            */
            Object<ObjectName> get_object() const noexcept
            {
                return object;
            }
        };

        //主系表句子
        template<class ReturnValue, class SubjectName, class ObjectName, class PredicateName, class ...Args>
        class Sentence<SentenceStructure::SUBJECT_PREDICATE_COMPLEMENT, ReturnValue, SubjectName, ObjectName, PredicateName, Args...>
        {
        private:
            Subject<SubjectName> subject;
            PredicateName predicate;
        public:
            Sentence() = delete;
            /**
            *@brief 构造主系表句子
            *@param sub：主语
            *@param pre：表语
            */
            Sentence(const Subject<SubjectName> &sub, const PredicateName &pre) : subject(sub), predicate(pre){}
            /**
            *@brief 说句子(执行句子)
            *@param args：执行句子需要的参数
            *@return 返回句子包
            */
            SentencePackSVP<SubjectName, PredicateName>say(Args... args)
            {
                return SentencePackSVP<SubjectName, PredicateName>{ subject, predicate };
            }
            /**
            *@brief 传入表语到自定义函数中检测
            *@param func：lambdaλ表达式
            *@param args：lambda需要的函数
            *@note lambda必须接受主语和表语，可选参数，必须返回bool
            *@return 返回bool
            */
            template<class Func, class ...FArgs>
            bool be(Func&& func, FArgs... args) const
            {
                return (func(subject, predicate, args...));
            }
            /**
            *@brief 获取主语
            */
            Subject<SubjectName> get_subject() const noexcept
            {
                return subject;
            }
            /**
            *@brief 获取表语
            */
            PredicateName get_predicate() const noexcept
            {
                return predicate;
            }
            /**
            *@brief 设置表语
            *@param pred：表语
            */
            void set_predicate(const PredicateName &pred)
            {
                this->predicate = pred;
            }
        };
    }
}

#endif