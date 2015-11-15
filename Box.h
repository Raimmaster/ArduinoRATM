#ifndef BOX_H
#define BOX_H


class Box
{
    public:
        float x, y, width, height;
        Box(float x, float y, float width, float height);
        virtual ~Box();
    protected:
    private:
};

#endif // BOX_H
