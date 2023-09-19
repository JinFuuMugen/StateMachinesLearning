class Impl{
    private:
        int Num;
        int Ind;
        int P;
        bool Pw;
        bool Inf;

        static int Count(int);      //Ones counter (essential for getting field of index Ind)

    public:
        explicit Impl(int);                  //Constr from impl number
        explicit Impl(bool);
        ~Impl();                    //Destr

        static Impl Patch(Impl*, Impl*);  //Method checks Quine McCluskey for checking possibility of gluing two imls
                                            //method changes Pw in both impls
                                            //returns new impl if possible
                                            //else returns null
                                            //contr calls in order to create a new impl
                                            //P field of new impl fills in by calling field inside this method
        bool operator != (const Impl&) const;
        int GetPw() const;
        int GetNum() const;
        int GetInd();
        int GetP() const;

        void setPw();

        bool isValid() const;
};