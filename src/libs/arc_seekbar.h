/************************************************************
 * Description: ���ν�����������ȱ��>20��
 * Author     : hookjc
 * C-Date     : 2023/4/29
 ************************************************************/

#ifndef __arc_seekbar_h__
#define __arc_seekbar_h__

#include "libs.h"

class ArcSeekBar : public View
{
public:    
    DECLARE_UIEVENT(void, OnArcSeekBarChangeListener, View &v, int progress);
    DECLARE_UIEVENT(void, OnArcSeekBarChangeListener2, View &v, int progress, bool fromUser);

public:
    ArcSeekBar(int w, int h);
    ArcSeekBar(Context *ctx, const AttributeSet &attr);
    ~ArcSeekBar();

    void setMin(int min);
    int  getMin();
    void setMax(int max);
    int  getMax();
    void setRange(int r0, int r2);
    void setProgress(int progress);
    int  getProgress();
    void setOnChangeListener(OnArcSeekBarChangeListener l);
    void setOnChangeListener2(OnArcSeekBarChangeListener2 l);
    void setShowSlider(bool Show);

protected:
    virtual void onMeasure(int widthMeasureSpec, int heightMeasureSpec);
    virtual void onDraw(Canvas &ctx);
    virtual bool onTouchEvent(MotionEvent &evt);

protected:
    static double ARC_EXTEND_ANGLE;
    enum emArcDrawStatus
    {
        ADS_DRAWING = 1,   // ������
        ADS_COMPLETE,      // �������
    };
    void  initViewData();
    float getRelativeDegrees(float x, float y);
    float getTouchDegrees(float x, float y);
    void  onDrawTimer();
    int   getWidthProgress();
    void  calcTouchState(int x, int y);
    void  checkRange(int &progress);

protected:
    int                        mWidth;             // �ɻ���Բ�Ŀ���
    int                        mHeight;            // �ɻ���Բ�Ŀ���
    int                        mCircleX;           // Բ������x
    int                        mCircleY;           // Բ������Y
    double                     mStartAngle;        // m/180.0*PI ��ʼ�Ƕ�
    double                     mEndAngle;          // M/180.0*PI �����Ƕ�
    int                        mBackgroundColor;   // ����ɫ
    int                        mBackgroundWidth;   // �������߿���    
    int                        mForegroundColor;   // ǰ��ɫ
    int                        mForegroundColor2;  // ǰ��ɫ2
    Cairo::Context::LineCap    mStrokeCap;         // �����˵���ʽ
    int                        mForegroundWidth;   // ǰ�����߿���
    int                        mRadius;            // Բ���뾶
    int                        mMin;               // ��Сֵ
    int                        mMax;               // ���ֵ
    int                        mProgress;          // ��ǰ����
    int                        mSliderRadius;      // ����뾶
    int                        mSliderWidth;       // ������������
    int                        mSliderColor;       // ����������ɫ
    int                        mSliderFillColor;   // ����Բ�������ɫ
    Drawable *                 mSlider;            // ����
    bool                       mShowSlider;        // �Ƿ���ʾ����
    RECT                       mRectSlider;        // ��������
    bool                       mSliderDown;        // �Ƿ�������    
    int                        mDrawStatus;        // �������״̬
    bool                       mShowProgressTxt;   // ��ʾ������ֵ
    bool                       mIsPercentProgress; // �ٷֱȽ���
    Paint                      mPaintTxt;          // �ı�����
    OnArcSeekBarChangeListener mOnChangeListener;  // ����仯�¼�
    OnArcSeekBarChangeListener2 mOnChangeListener2;  // ����仯�¼�
    int                        mTouchLastX;
    int                        mTouchLastY;
    uchar                      mAngleAdd:1;        // ��������
    int                        mRange[2];          // �ɻ�����Χ
    bool                       mFromUser;
};

#endif
