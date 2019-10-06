#include "cartoonEffect.h"

cv::Mat cartoonEffect(cv::Mat image)
{
	cv::Mat gaussianblurred;
	cv::GaussianBlur(image, gaussianblurred, cv::Size(5, 5), 0);

	cv::Mat mediablurred;
	cv::medianBlur(gaussianblurred, mediablurred, 7);

	cv::Mat reduced = reduceColor(mediablurred);
	cv::Mat edges = detectEdges(reduced);

	cv::Mat blurredEdges;
	cv::GaussianBlur(edges, blurredEdges, cv::Size(3, 3), 3);

	cv::Mat blurredEdges3C;
	cv::cvtColor(blurredEdges, blurredEdges3C, cv::COLOR_GRAY2BGR);

	cv::Mat finalResult;
	cv::subtract(reduced, blurredEdges3C, finalResult);
	
	cv::imshow("final result", finalResult);
	cv::waitKey(0);

	return finalResult;
}

std::vector<cv::Mat> cartoonEffect(const InputHandler &inputHandler)
{
    std::vector<cv::Mat> images = inputHandler.getImages();
	std::vector<cv::Mat> result;

	for (int i = 0; i < images.size(); ++i) {
		cv::Mat resultI = cartoonEffect(images.at(i));
		result.push_back(resultI);
	}

	return result;
}
