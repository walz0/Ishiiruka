#pragma once

#include "Common/CommonTypes.h"
#include <atomic>
#include <curl/curl.h>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

class SlippiUser
{
  public:
	enum SlippiRank
	{
		RANK_UNRANKED,
		RANK_BRONZE_1,
		RANK_BRONZE_2,
		RANK_BRONZE_3,
		RANK_SILVER_1,
		RANK_SILVER_2,
		RANK_SILVER_3,
		RANK_GOLD_1,
		RANK_GOLD_2,
		RANK_GOLD_3,
		RANK_PLATINUM_1,
		RANK_PLATINUM_2,
		RANK_PLATINUM_3,
		RANK_DIAMOND_1,
		RANK_DIAMOND_2,
		RANK_DIAMOND_3,
		RANK_MASTER_1,
		RANK_MASTER_2,
		RANK_MASTER_3,
		RANK_GRANDMASTER,
	};

	struct UserInfo
	{
		std::string uid = "";
		std::string playKey = "";
		std::string displayName = "";
		std::string connectCode = "";
		std::string latestVersion = "";
		std::string fileContents = "";

		int port;
	};

	struct RankInfo
	{
		SlippiRank rank;
		float ratingOrdinal;
		int globalPlacing;
		int regionalPlacing;
	};

	SlippiUser();
	~SlippiUser();

	bool AttemptLogin();
	void OpenLogInPage();
	bool UpdateApp();
	void ListenForLogIn();
	void LogOut();
	void OverwriteLatestVersion(std::string version);
	UserInfo GetUserInfo();
	bool IsLoggedIn();
	void FileListenThread();

	RankInfo GetRankInfo(std::string connectCode);
	SlippiRank GetRank(float ratingOrdinal, int globalPlacing, int regionalPlacing);

  protected:
	UserInfo parseFile(std::string fileContents);
	void deleteFile();
	void overwriteFromServer();

	UserInfo userInfo;
	bool isLoggedIn = false;

	const std::string URL_START = "https://users-rest-dot-slippi.uc.r.appspot.com/user";
	CURL *m_curl = nullptr;
	struct curl_slist *m_curlHeaderList = nullptr;
	std::vector<char> receiveBuf;

	std::thread fileListenThread;
	std::atomic<bool> runThread;
};
