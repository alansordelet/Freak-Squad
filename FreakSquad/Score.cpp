//#include "Score.h"
//#include "FeedBackScore.h"
//#include "Camera.h"
//#include "Ui.h"
//#include "Ui_Player.h"
//
//void Score::TimeScore(float* _time, int* _score1, int* _score2)
//{
//	if (*_time < 5.0f)
//	{
//		*_score1 *= 1.5;
//		*_score2 *= 1.5;
//	}
//	else if (*_time > 5.0f && *_time < 10.0f)
//	{
//		*_score1 *= 1.35;
//		*_score2 *= 1.35;
//	}
//	else if (*_time > 10.0f && *_time < 15.0f)
//	{
//		*_score1 *= 1.2;
//		*_score2 *= 1.2;
//	}
//	else if (*_time > 15.0f && *_time < 20.0f)
//	{
//		*_score1 *= 1;
//		*_score2 *= 1;
//	}
//	else
//	{
//		*_score1 *= 0.5;
//		*_score2 *= 0.5;
//	}
//
//	*_time = 0.0f;
//}
//
//Score::~Score()
//{
//}
//Score::Score()
//{
//	m_iHitJ1 = 0;
//	m_iHitJ2 = 0;
//	m_iScoreJ1 = 0;
//	m_iScoreJ2 = 0;
//	m_iNbHit = 0;
//	m_timerHit = 0.0f;
//
//	//s_stHit1 = { "Hit : " };
//	//m_txHit.setFont(RessourceManager::get()->getFont("PurpleSmile.ttf"));
//	//m_txHit.setFillColor(sf::Color::Red);
//	//m_txHit.setPosition(sf::Vector2f(900.0f,0.0f));
//
//	m_txScoreJ1.setFont(RessourceManager::get()->getFont("Scoring.otf"));
//	m_txScoreJ1.setFillColor(sf::Color::White);
//	m_txScoreJ1.setOutlineThickness(5.0f);
//	m_txScoreJ1.setOutlineColor(sf::Color::Black);
//	m_txScoreJ1.setPosition(sf::Vector2f(420.0f, 40.0f));
//	m_txScoreJ1.setCharacterSize(50.0f);
//
//	m_txScoreJ2.setFont(RessourceManager::get()->getFont("Scoring.otf"));
//	m_txScoreJ2.setFillColor(sf::Color::White);
//	m_txScoreJ2.setOutlineThickness(5.0f);
//	m_txScoreJ2.setOutlineColor(sf::Color::Black);
//	m_txScoreJ2.setPosition(sf::Vector2f(1750.0f, 40.0f));
//	m_txScoreJ2.setCharacterSize(50.0f);
//
//	m_bInteruption = false;
//
//}
//void Score::update()
//{
//	if (m_iScoreJ1 < 10)
//		s_stScore1 = { "000 00" };
//	else if (m_iScoreJ1 >= 10 && m_iScoreJ1 < 100)
//		s_stScore1 = { "000 0" };
//	else if (m_iScoreJ1 >= 100 && m_iScoreJ1 < 1000)
//		s_stScore1 = { "000 " };
//	else if (m_iScoreJ1 >= 1000 && m_iScoreJ1 < 10000)
//		s_stScore1 = { "00" };
//	else if (m_iScoreJ1 >= 10000 && m_iScoreJ1 < 100000)
//		s_stScore1 = { "0" };
//	else
//		s_stScore1 = { "" };
//
//	if (m_iScoreJ2 < 10)
//		s_stScore2 = { "000 00" };
//	else if (m_iScoreJ2 >= 10 && m_iScoreJ2 < 100)
//		s_stScore2 = { "000 0" };
//	else if (m_iScoreJ2 >= 100 && m_iScoreJ2 < 1000)
//		s_stScore2 = { "000 " };
//	else if (m_iScoreJ2 >= 1000 && m_iScoreJ2 < 10000)
//		s_stScore2 = { "00" };
//	else if (m_iScoreJ2 >= 10000 && m_iScoreJ2 < 100000)
//		s_stScore2 = { "0" };
//	else
//		s_stScore2 = { "" };
//
//	m_iNbHit = m_iHitJ1 + m_iHitJ2;
//	m_stNbHit = std::to_string(m_iNbHit);
//
//	if (auto Parent = getParents().lock())
//	{
//		Parent->getParent()->getObjects("Ui")->getComponents<FeedBackScore>()->m_txHit.setString(Parent->getParent()->getObjects("Ui")->getComponents<FeedBackScore>()->s_stHit1 + m_stNbHit);
//	}
//
//
//	m_stiScore1 = std::to_string(m_iScoreJ1);
//
//	m_stiScore2 = std::to_string(m_iScoreJ2);
//	m_txScoreJ2.setString(s_stScore2 + m_stiScore2);
//
//	m_timerHit += tools::GetTimeDelta();
//
//	if (m_timerHit > 3.0)
//	{
//		if (auto Parent = getParents().lock())
//		{
//			auto parent = Parent->getParent()->getObjects("UIPlayer")->getComponents<Ui>();
//			if(parent->getPlayerNumber() == 1)
//				AjoutScoreSolo(&m_iNbHit, &m_iHitJ1, &m_iScoreJ1);
//			if(parent->getPlayerNumber() == 2)
//				AjoutScoreCoop(&m_iNbHit, &m_iHitJ1, &m_iHitJ2, &m_iScoreJ1, &m_iScoreJ2);
//		}
//	}
//
//	std::string numberString = std::to_string(m_iScoreJ1);
//	int number;
//	std::stringstream(numberString) >> number;
//
//	std::stringstream formattedStringStream;
//	formattedStringStream.imbue(std::locale(""));
//	formattedStringStream << number;
//	std::string formattedString = formattedStringStream.str();
//
//
//	m_txScoreJ1.setString(s_stScore1 + formattedString);
//
//
//	std::string numberString2 = std::to_string(m_iScoreJ2);
//	int number2;
//	std::stringstream(numberString2) >> number2;
//
//	std::stringstream formattedStringStream2;
//	formattedStringStream2.imbue(std::locale(""));
//	formattedStringStream2 << number2;
//	std::string formattedString2 = formattedStringStream2.str();
//
//	m_txScoreJ2.setString(s_stScore2 + formattedString2);
//}
//
//int Score::ajoutChoixScore() {
//	m_choixS = 6;
//	return m_choixS;
//}
//
//void Score::hitJ1(int* _nbScore)
//{
//	if (auto Parent = getParents().lock())
//	{
//		auto parent = Parent->getParent()->getObjects("UIPlayer");
//
//		auto uiPlayer = parent->getComponents<Ui_Player>();
//		auto score = parent->getComponents<Score>();
//
//		score->m_iHitJ1 += 1;
//		score->m_iScoreJ1 += *_nbScore;
//		timer = 0.0f;
//		score->m_timerHit = 0.0f;
//
//		if (auto Parent2 = getParents().lock())
//		{
//			auto parent2 = Parent2->getParent()->getObjects("Ui");
//			auto feedbasckscore = parent2->getComponents<FeedBackScore>();
//			feedbasckscore->m_newscaleEG = { 1.0f,1.0f };
//			feedbasckscore->m_scaleEG = { 1.0f,1.0f };
//			feedbasckscore->m_timerEG = 0.0f;
//			feedbasckscore->m_activeEG = true;
//			feedbasckscore->m_stoprotation = true;
//		}
//
//		uiPlayer->algoUlt();
//	}
//
//}
//void Score::hitJ2(int* _nbScore)
//{
//	if (auto Parent = getParents().lock())
//	{
//		auto parent = Parent->getParent()->getObjects("UIPlayer");
//
//		auto uiPlayer = parent->getComponents<Ui_Player>();
//		auto score = parent->getComponents<Score>();
//
//		score->m_iHitJ2 += 1;
//		score->m_iScoreJ2 += *_nbScore;
//		timer = 0.0f;
//		score->m_timerHit = 0.0f;
//
//		if (auto Parent2 = getParents().lock())
//		{
//			auto parent2 = Parent2->getParent()->getObjects("Ui");
//			auto feedbasckscore = parent2->getComponents<FeedBackScore>();
//			feedbasckscore->m_newscaleEG = { 1.0f,1.0f };
//			feedbasckscore->m_scaleEG = { 1.0f,1.0f };
//			feedbasckscore->m_timerEG = 0.0f;
//			feedbasckscore->m_activeEG = true;
//			feedbasckscore->m_stoprotation = true;
//		}
//
//
//		uiPlayer->algoUlt();
//	}
//}
//
//void Score::draw()
//{
//	window.getWindow().setView(window.getWindow().getDefaultView());
//	if (auto Parent = getParents().lock())
//	{
//		if (m_iNbHit > 0)
//		{
//			this->window.draw(Parent->getParent()->getObjects("Ui")->getComponents<FeedBackScore>()->m_txHit);
//		}
//	}
//	this->window.draw(m_txScoreJ1);
//	this->window.draw(m_txScoreJ2);
//	/*if (auto Parent = getParents().lock())
//	{
//		window.getWindow().setView(Parent->getObjects("Camera")->getComponents<Camera>()->getView());
//	}*/
//}
//
//void Score::AjoutScoreSolo(int* _nbHit, int* _hitJ1, int* _score1) {
//	int tmp_value;
//	tmp_value = *_hitJ1 * ((*_nbHit / 10) + 1);
//	*_score1 += tmp_value;
//	*_nbHit = 0; *_hitJ1 = 0;
//	InteruptionScoreSolo(_nbHit, _hitJ1);
//}
//void Score::AjoutScoreCoop(int* _nbHit, int* _hitJ1, int* _hitJ2, int* _score1, int* _score2) {
//	int tmp_value, tmp_value2;
//	tmp_value = *_hitJ1 * ((*_nbHit / 10) + 1);
//	tmp_value2 = *_hitJ2 * ((*_nbHit / 10) + 1);
//	*_score1 += tmp_value;
//	*_score2 += tmp_value2;
//	*_nbHit = 0; *_hitJ1 = 0; *_hitJ2 = 0;
//	InteruptionScoreCoop(_nbHit, _hitJ1, _hitJ2);
//}
//
//void Score::InteruptionScoreCoop(int* _nbHit, int* _hitJ1, int* _hitJ2) {
//	*_nbHit = 0;	*_hitJ1 = 0;	*_hitJ2 = 0;
//}
//
//void Score::InteruptionScoreSolo(int* _nbHit, int* _hitJ1) {
//	*_nbHit = 0;	*_hitJ1 = 0;;
//}