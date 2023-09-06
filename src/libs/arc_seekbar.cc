
#include "arc_seekbar.h"

DECLARE_WIDGET(ArcSeekBar)

double ArcSeekBar::ARC_EXTEND_ANGLE = 10.0;

ArcSeekBar::ArcSeekBar(int w, int h) : View(w, h) { initViewData(); }

ArcSeekBar::ArcSeekBar(Context *ctx, const AttributeSet &attrs) : View(ctx, attrs) {
    initViewData();

    mBackgroundColor = attrs.getColor("colorBackground", 0xff424242);
    mBackgroundWidth = attrs.getDimensionPixelSize("widthBackground", mBackgroundWidth);

    mForegroundColor  = attrs.getColor("colorForeground", mForegroundColor);
    mForegroundColor2 = attrs.getColor("colorForeground2", mForegroundColor);
    mForegroundWidth = attrs.getDimensionPixelSize("widthForeground", mBackgroundWidth);

    mRadius = attrs.getDimensionPixelSize("radius", 80);

    mStartAngle = attrs.getInt("startAngle", 150);
    mEndAngle   = attrs.getInt("endAngle", 390);

    mMin      = attrs.getInt("min", mMin);
    mMax      = attrs.getInt("max", mMax);
    mProgress = attrs.getInt("progress", mProgress);    

    mSliderRadius    = attrs.getDimensionPixelSize("sliderRadius", 14);
    mSliderWidth     = attrs.getDimensionPixelSize("sliderWidth", 1);
    mSliderColor     = attrs.getColor("sliderColor", mSliderColor);
    mSliderFillColor = attrs.getColor("sliderFillColor", mSliderFillColor);

    mSlider = attrs.getDrawable("slider");

    mShowSlider        = attrs.getBoolean("showSlider", true);
    mShowProgressTxt   = attrs.getBoolean("showProgressText", mShowProgressTxt);
    mIsPercentProgress = attrs.getBoolean("isPercentProcess", mIsPercentProgress);

    mStrokeCap = (Cairo::Context::LineCap)attrs.getInt(
        "strokeCap",
        std::map<const std::string, int>{{"butt", (int)Cairo::Context::LineCap::BUTT},
                                         {"round", (int)Cairo::Context::LineCap::ROUND},
                                         {"square", (int)Cairo::Context::LineCap::SQUARE}},
        (int)mStrokeCap);

    LOG(VERBOSE) << "radius=" << mRadius << " startAngle=" << mStartAngle << " endAngle=" << mEndAngle;
}

ArcSeekBar::~ArcSeekBar() {}

void ArcSeekBar::initViewData() {
    mBackgroundColor  = 0xff424242;
    mBackgroundWidth  = 20;
    mForegroundColor  = 0xffB7B7B7;
    mForegroundWidth  = 20;
    mRadius           = 80;
    mStartAngle       = 150;
    mEndAngle         = 390;
    mMin              = 0;
    mMax              = 100;
    mProgress         = 30;
    mSliderRadius     = 14;
    mSliderWidth      = 1;
    mSliderColor      = 0xffd9d9d9;
    mSliderFillColor  = 0xffd9d9d9;
    mShowSlider       = true;
    mSliderDown       = false;
    mOnChangeListener = nullptr;     
    mOnChangeListener2 = nullptr;   
    mForegroundColor2 = mForegroundColor;
    mTouchLastX       = 0;
    mTouchLastY       = 0;
    mFromUser         = false;   

    mShowProgressTxt   = false;
    mIsPercentProgress = false;
    mPaintTxt.setColor(Color::WHITE);
    mPaintTxt.setTextSize((mRadius - MAX(mBackgroundWidth, mForegroundWidth) / 2.0) * 0.65);

    mStrokeCap = Cairo::Context::LineCap::ROUND;
    bzero(mRange, sizeof(mRange));
}

void ArcSeekBar::onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
    View::onMeasure(widthMeasureSpec, heightMeasureSpec);

    mWidth  = getMeasuredWidth();
    mHeight = getMeasuredHeight();

    mCircleX = mWidth / 2;
    mCircleY = mHeight / 2;

    LOG(VERBOSE) << "w=" << mWidth << " h=" << mHeight << " cx=" << mCircleX << " cy=" << mCircleY;
}

void ArcSeekBar::onDraw(Canvas &ctx) {
    View::onDraw(ctx);

    int progress = mProgress; 

    checkRange(progress);

    // 背景
    Paint fPaint(ctx);
    fPaint.setStrokeWidth(mBackgroundWidth);
    fPaint.setColor(mBackgroundColor);
    fPaint.setStrokeCap(mStrokeCap);
    fPaint.drawArc(mCircleX, mCircleY, mRadius, mStartAngle, mEndAngle);

    int endAngle = mStartAngle + (mEndAngle - mStartAngle) * (progress - mMin) / getWidthProgress();
    LOG(VERBOSE) << getId() << " progress=" << progress << " end=" << endAngle;

    // 前景
    if (endAngle > mStartAngle) {
        if (mForegroundColor == mForegroundColor2) {
            Paint sPaint(ctx);
            sPaint.setStrokeWidth(mForegroundWidth);
            sPaint.setColor(mForegroundColor);
            sPaint.setStrokeCap(mStrokeCap);
            sPaint.drawArc(mCircleX, mCircleY, mRadius, mStartAngle, endAngle);
        } else {
            cairo_t *cr = ctx.cobj();
            // 创建线性渐变
            cairo_pattern_t *gradient = cairo_pattern_create_linear(mCircleX - mRadius, mCircleY, mCircleX + mRadius, mCircleY);
            Color gradient_c(mForegroundColor);
            Color gradient_c2(mForegroundColor2);
            cairo_pattern_add_color_stop_rgb(gradient, 0, gradient_c.red(), gradient_c.green(), gradient_c.blue()); // 起始颜色
            cairo_pattern_add_color_stop_rgb(gradient, 1, gradient_c2.red(), gradient_c2.green(), gradient_c2.blue()); // 终止颜色
            
            cairo_new_path(cr);
            cairo_arc(cr, mCircleX, mCircleY, mRadius, mStartAngle * M_PI / 180.0, endAngle * M_PI / 180.0);
            cairo_set_line_width(cr, mForegroundWidth);
            cairo_set_line_cap(cr, static_cast<cairo_line_cap_t>(mStrokeCap));
            cairo_set_source(cr, gradient);
            cairo_stroke(cr);
        }        
    }

    // 滑块
    if (mShowSlider) {
        int x = mCircleX + mRadius * cos(endAngle * M_PI / 180.0);
        int y = mCircleY + mRadius * sin(endAngle * M_PI / 180.0);

        if (mSlider != nullptr) {
            mRectSlider.width  = mSlider->getIntrinsicWidth();
            mRectSlider.height = mSlider->getIntrinsicHeight();
            mRectSlider.left   = x - mRectSlider.width / 2;
            mRectSlider.top    = y - mRectSlider.height / 2;

            mSlider->setBounds(mRectSlider);
            mSlider->draw(ctx);
        } else {
            Paint silder(ctx);
            silder.setStrokeWidth(mSliderWidth);
            silder.setColor(mSliderColor);
            silder.setFillColor(mSliderFillColor);
            silder.setStyle(Paint::FILL_AND_STROKE);
            silder.drawArc(x, y, mSliderRadius, 0, 360);

            mRectSlider.width  = (mSliderWidth + mSliderRadius) * 2;
            mRectSlider.height = mRectSlider.width;
            mRectSlider.left   = x - mRectSlider.width / 2;
            mRectSlider.top    = y - mRectSlider.height / 2;
        }
    }

    // 进度值
    if (mShowProgressTxt) {
        std::string showTxt = std::to_string((int)progress);
        if (mIsPercentProgress)
            showTxt += "%";
        mPaintTxt.drawText(mCircleX - mRadius, mCircleY - mRadius, mRadius * 2, mRadius * 2, showTxt, Gravity::CENTER,
                           &ctx);
    }
}

bool ArcSeekBar::onTouchEvent(MotionEvent &evt) {
    if (!mShowSlider || !isEnabled()) {
        return false;
    }

    LOG(VERBOSE) << "action=" << evt.getAction() << " x=" << evt.getX() << " y=" << evt.getY();

    switch (evt.getAction()) {
    case MotionEvent::ACTION_DOWN:
        mSliderDown = mRectSlider.contains(evt.getX(), evt.getY());
        if (!mSliderDown) {
            // 未点击滑块，必须点击在弧上
            int angle = getRelativeDegrees(evt.getX(), evt.getY());
            if (angle >= mStartAngle - ARC_EXTEND_ANGLE && angle <= mEndAngle + ARC_EXTEND_ANGLE) // 满足弧线内
            {
                RECT rc;
                int  x    = mCircleX + mRadius * cos(angle * M_PI / 180.0);
                int  y    = mCircleY + mRadius * sin(angle * M_PI / 180.0);
                rc.width  = mBackgroundWidth;
                rc.height = mBackgroundWidth;
                rc.left   = x - rc.width / 2;
                rc.top    = y - rc.height / 2;
                if (rc.contains(evt.getX(), evt.getY())) {
                    mFromUser = true;
                    setProgress(mMin + getWidthProgress() * (angle - mStartAngle) / (mEndAngle - mStartAngle));
                    mFromUser = false;
                }
            }
        }
        break;
    case MotionEvent::ACTION_UP:
        mSliderDown = false;
        break;
    case MotionEvent::ACTION_MOVE:
        if (mSliderDown) {
            calcTouchState(evt.getX(), evt.getY());
            int angle = getRelativeDegrees(evt.getX(), evt.getY());
            if (angle >= mStartAngle - ARC_EXTEND_ANGLE) {
                int progress = mMin + getWidthProgress() * (angle - mStartAngle) / (mEndAngle - mStartAngle);
                if (mAngleAdd) {
                    if (progress < mProgress && mProgress - mMin > (mMax-mMin)*7/8) {
                        progress = mMax; // 已经滑到最大[边缘抖动]
                    } else if (mProgress == mMin) {
                        if (progress - mMin > (mMax-mMin)/8) {
                            break; // 需要逐渐增加
                        }
                    }
                } else {
                    if (progress > mProgress && mProgress - mMin < (mMax-mMin)/8) {
                        progress = mMin;  // 已经滑到最小
                    } else if (mProgress == mMax) {
                        if (progress - mMin < (mMax-mMin)*7/8){
                            break; // 需要逐渐减少
                        }
                    }
                }
                LOG(VERBOSE) << "angle=" << angle << " progress=" << progress;
                mFromUser = true;
                setProgress(progress);
                mFromUser = false;
            }
        }
        break;
    }

    mTouchLastX = evt.getX();
    mTouchLastY = evt.getY();

    return mSliderDown || View::onTouchEvent(evt);
}

/**
 * 获取触摸坐标的夹角度数
 * @param x
 * @param y
 * @return
 */
float ArcSeekBar::getTouchDegrees(float x, float y) {
    double x1 = x - mCircleX;
    double y1 = y - mCircleY;

    double arcNum   = atan2(y1, x1);
    double angleNum = arcNum * 180 / M_PI;

    LOG(VERBOSE) << "y=" << y1 << " x=" << x1 << " arc=" << arcNum << " angle=" << angleNum;

    return angleNum;
}

float ArcSeekBar::getRelativeDegrees(float x, float y) {    
    double angleNum = getTouchDegrees(x, y);    

    if (angleNum < 0 || angleNum < mStartAngle) {
        angleNum += 360;
    }
    if (angleNum < mStartAngle) {
        angleNum += 360;
    }

    LOG(VERBOSE) << "relative angle=" << angleNum;

    return angleNum;
}

void ArcSeekBar::setMin(int min) { mMin = min; }

int ArcSeekBar::getMin() { return mMin; }

void ArcSeekBar::setMax(int max) { mMax = max; }

int ArcSeekBar::getMax() { return mMax; }

void ArcSeekBar::setProgress(int progress) {
    int nProgress = progress;
    if (nProgress > mMax)
        nProgress = mMax;
    else if (nProgress < mMin)
        nProgress = mMin;

    checkRange(nProgress);

    if (nProgress == mProgress) return;

    LOGV("%d set progress. old=%d new=%d", getId(), mProgress, nProgress);

    int oldProgress = mProgress;
    mProgress = nProgress;

    if (mOnChangeListener) {
        mOnChangeListener(*this, mProgress);
    }
    if (mOnChangeListener2) {
        mOnChangeListener2(*this, mProgress, mFromUser);
    }

    invalidate();
}

int ArcSeekBar::getProgress() { return mProgress; }

void ArcSeekBar::setOnChangeListener(OnArcSeekBarChangeListener l) { mOnChangeListener = l; }
void ArcSeekBar::setOnChangeListener2(OnArcSeekBarChangeListener2 l) { mOnChangeListener2 = l; }
void ArcSeekBar::setShowSlider(bool Show) {mShowSlider = Show; }
int ArcSeekBar::getWidthProgress() {
    return std::max(1, mMax - mMin);
}

void ArcSeekBar::calcTouchState(int x, int y) {
    float lastAngle  = getTouchDegrees(mTouchLastX, mTouchLastY);
    float currAngle = getTouchDegrees(x, y);

    // 顺时针，加
    if (x < mCircleX || y < mCircleY) {
        if (lastAngle > 0) {
            if (currAngle > lastAngle || currAngle < 0) {
                mAngleAdd = 1;
                LOGV("angle add %.2f %.2f", lastAngle, currAngle);
                return;
            }
        } else {
            if (currAngle < 0 && currAngle > lastAngle) {
                mAngleAdd = 1;
                LOGV("angle add %.2f %.2f", lastAngle, currAngle);
                return;
            }
        }
    } else if (currAngle > lastAngle){
        mAngleAdd = 1;
        LOGV("angle add %.2f %.2f", lastAngle, currAngle);
        return;
    }

    // 逆时针，减
    mAngleAdd = 0;
    LOGV("angle dec %.2f %.2f", lastAngle, currAngle);
}

void ArcSeekBar::setRange(int r0, int r2) {
    if (r0 >= mMin && r2 <= mMax && r0 < r2) {
        mRange[0] = r0;
        mRange[1] = r2;
    } else {
        bzero(mRange, sizeof(mRange));
    }
}

void ArcSeekBar::checkRange(int &progress) {
    if (mRange[0] >= mMin && mRange[1] <= mMax && mRange[0] < mRange[1]) {
        if (progress > mRange[1]) {
            LOGV("change to up %d=>%d", progress, mRange[1]);
            progress = mRange[1];            
        } else if (progress < mRange[0]) {
            LOGV("change to down %d=>%d", progress, mRange[0]);
            progress = mRange[0];
        }
    }
}
