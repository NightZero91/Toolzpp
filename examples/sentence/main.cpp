/**
 * @file main.cpp
 * @brief Example usage of toolzpp sentence module
 * @copyright MIT License
 *
 * This example demonstrates the natural language style event binding
 * using Subject, Object, and Sentence classes.
 *
 */

#include "sentencepp.h"
#include <functional>
#include <iostream>
#include <string>

using namespace tlz::sentence;

// ============ Simple Action Functions ============

void print_message(std::string msg) {
  std::cout << "[LOG] " << msg << std::endl;
}

void process_data(Object<std::string> &obj, std::string action) {
  std::cout << "[PROCESS] " << action << " " << obj.get() << std::endl;
}

void validate_age(Subject<std::string> &sub, int age) {
  std::cout << "[VALIDATE] " << sub.get() << " is " << age << " years old"
            << std::endl;
}

// ============ Custom Class for Event Demo ============

class Button {
  std::string label;

public:
  Button(const std::string &lbl) : label(lbl) {}
  void click() {
    std::cout << "[BUTTON] " << label << " clicked!" << std::endl;
  }
  std::string get_label() const { return label; }
};

class Message {
  std::string content;

public:
  Message(const std::string &msg) : content(msg) {}
  void deliver() {
    std::cout << "[MESSAGE] Delivered: " << content << std::endl;
  }
  std::string get_content() const { return content; }
};

// ============ Main Example ============

int main() {
  std::cout << "========== Sentence Module Examples ==========\n\n";

  // ----- Example 1: Subject-Predicate (SV) -----
  std::cout << "--- Example 1: SV (Subject-Predicate) ---\n";

  Subject<std::string> logger("Logger");
  Sentence<tlz::SentenceStructure::SUBJECT_PREDICATE, void, std::string,
           nullname, nullname, std::string>
      logger_sentence(logger, std::function<void(std::string)>(print_message));

  auto pack = logger_sentence.say("System started");
  pack.then(logger_sentence, " Initialization complete");

  std::cout << "\n";

  // ----- Example 2: Subject-Predicate-Object (SVO) -----
  std::cout << "--- Example 2: SVO (Subject-Predicate-Object) ---\n";

  Subject<std::string> worker("Worker");
  Object<std::string> data("database.txt");

  Sentence<tlz::SentenceStructure::SUBJECT_PREDICATE_OBJECT, void, std::string,
           std::string, nullname, std::string>
      processor(worker, data,
                std::function<void(Object<std::string> &, std::string)>(
                    process_data));

  processor.say("reading");
  processor.say("writing");

  std::cout << "\n";

  // ----- Example 3: Subject-Predicate-Complement (SVP) -----
  std::cout << "--- Example 3: SVP (Subject-Predicate-Complement) ---\n";

  Subject<std::string> person("Alice");
  Sentence<tlz::SentenceStructure::SUBJECT_PREDICATE_COMPLEMENT, void,
           std::string, nullname, int>
      age_check(person, 25);

  auto age_pack = age_check.say();

  // Test the complement predicate
  bool is_adult = age_check.be(
      [](const Subject<std::string> &sub, int age) { return age >= 18; });

  std::cout << "[CHECK] " << person.get() << " is adult: " << std::boolalpha
            << is_adult << "\n";

  // Modify the predicate
  age_check.set_predicate(30);
  std::cout << "[UPDATE] Age changed to " << age_check.get_predicate() << "\n";

  std::cout << "\n";

  // ----- Example 4: Event Binding (Button Click → Message) -----
  std::cout << "--- Example 4: Event Binding (Button → Message) ---\n";

  Button btn("Submit");
  Message msg("Form submitted");

  Subject<Button> button_subject(btn);
  Object<Message> message_object(msg);

  // Event handler: when button clicked, deliver message
  auto event_handler = [](Object<Message> &msg_obj) {
    msg_obj.get().deliver();
  };

  Sentence<tlz::SentenceStructure::SUBJECT_PREDICATE_OBJECT, void, Button,
           Message, nullname>
      button_binding(button_subject, message_object, event_handler);

  // Trigger the event
  std::cout << "[EVENT] Button click simulation:\n";
  button_binding.get_subject().get().click();
  button_binding.say();

  std::cout << "\n";

  // ----- Example 5: Chain of sentences -----
  std::cout << "--- Example 5: Chain of Sentences ---\n";

  Subject<std::string> chain_subject("Chain");

  Sentence<tlz::SentenceStructure::SUBJECT_PREDICATE, void, std::string,
           nullname, nullname, std::string>
      step1(chain_subject,
            [](std::string s) { std::cout << "[STEP1] " << s << std::endl; });

  Sentence<tlz::SentenceStructure::SUBJECT_PREDICATE, void, std::string,
           nullname, nullname, std::string>
      step2(chain_subject,
            [](std::string s) { std::cout << "[STEP2] " << s << std::endl; });

  Sentence<tlz::SentenceStructure::SUBJECT_PREDICATE, void, std::string,
           nullname, nullname, std::string>
      step3(chain_subject,
            [](std::string s) { std::cout << "[STEP3] " << s << std::endl; });

  step1.say("Initialize").then(step2, "Process").then(step3, "Complete");

  std::cout << "\n";

  // ----- Example 6: Conditional execution -----
  std::cout << "--- Example 6: Conditional Execution ---\n";

  bool debug_mode = true;

  Subject<std::string> debug_subject("Debug");
  Sentence<tlz::SentenceStructure::SUBJECT_PREDICATE, void, std::string,
           nullname, nullname, std::string>
      debug_log(debug_subject, [](std::string s) {
        std::cout << "[DEBUG] " << s << std::endl;
      });

  debug_log.say("Entering function")
      .if_then(debug_mode, debug_log, "Debug mode is ENABLED")
      .then(debug_log, "Exiting function");

  std::cout << "\n========== End of Examples ==========\n";

  return 0;
}