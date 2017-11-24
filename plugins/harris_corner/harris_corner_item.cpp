
#include "harris_corner_item.h"

#include "streams/sparse.h"
#include "streams/sparse_m.h"

HarrisCornerItem::HarrisCornerItem()
    : roviz::Item("HarrisEdge")
{
    ROVIZ_INIT_ITEM(HarrisCorner);

    this->input = this->addInput<roviz::Image>("Input");
    this->output = this->addOutput<roviz::Sparse<roviz::Point2D> >("Output");

    this->trim_block_size = this->addTrim(
                "Block Size", 2, 1, 10);

    this->trim_aperture_size = this->addTrim(
                "Aperture Size", 3, 1, 11, 2.);

    this->trim_k_param = this->addTrim(
                "k-Parameter", 0.04, 0.01, 0.5, 0.005);

    this->trim_threshold = this->addTrim(
                "Threshold", 200, 0, 255);
}

HarrisCornerItem::~HarrisCornerItem()
{
    this->stop();
}

void HarrisCornerItem::thread()
{
    while(this->input.waitForInput())
    {
        roviz::Image src = this->input.next();

        if(src.format() != roviz::Image::Gray8)
            continue;

        cv::Mat dst, dst_norm;
        dst = cv::Mat::zeros(src.height(), src.width(), CV_32FC1);

        cv::cornerHarris(src.toCv(), dst,
                         this->trim_block_size.value(),
                         this->trim_aperture_size.value(),
                         this->trim_k_param.value());

        // Normalize the output
        // TODO Optimize that by doing it manually in the other loop?
        cv::normalize(dst, dst_norm, 0, 255, cv::NORM_MINMAX, CV_8U);

        roviz::SparseMutable<roviz::Point2D> out(src, {src.id()});
        unsigned char *p = dst_norm.data;
        int thres = trim_threshold.value();
        int count = 0;
        for(int y = 0; y < dst_norm.rows; y++)
        {
            for(int x = 0; x < dst_norm.cols; x++)
            {
                if(*p >= thres)
                {
                    out.add(roviz::Point2D(x, y));
                    count++;
                }

                p++;
            }
        }
        std::cout << "Count: " << count << std::endl;
        this->output.pushOut(out);
    }
}
