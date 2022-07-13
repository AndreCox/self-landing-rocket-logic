class StateMachine {
 public:
  void update();
  void progress();
  void reset();

 private:
  int currentState = 0;
};