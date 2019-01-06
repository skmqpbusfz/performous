#pragma once

#include "fs.hh"

#include <boost/locale.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

#define _(x) boost::locale::translate(x).str()
#define translate_noop(x) x

class TranslationEngine {
public:
	TranslationEngine(const char *package) {
		// boost::locale::generator gen;
		// gen.add_messages_path(getLocaleDir().string());
		// gen.add_messages_domain(package);
		// try {
		// 	std::locale::global(gen(boost::locale::util::get_system_locale(true)));
		// } catch (...) {
		// 	std::clog << "locale/warning: Unable to detect locale, will try to fallback to en_US.UTF-8" << std::endl;
		// 	std::locale::global(gen("en_US.UTF-8"));
		// }
		m_gen.add_messages_path(getLocaleDir().string());
		m_gen.add_messages_domain(package);
		setLanguage("");
	};
	static bool enabled() {
		return true;
	};

	void setLanguage(const std::string language) { 
		std::cout << "languag: '"<<language<<"'"<<std::endl;
		m_currentLanguage = getLanguage(language);
		std::cout << "found languag: '"<<m_currentLanguage<<"'"<<std::endl;

		try {
			std::locale::global(m_gen(m_currentLanguage));
		std::cout << "lsetted correctly "<<std::endl;
		} catch (...) {
			std::clog << "locale/warning: Unable to detect locale, will try to fallback to en_US.UTF-8" << std::endl;
			std::locale::global(m_gen("en_US.UTF-8"));	
		}
	}

	const std::string getLanguage(const std::string language) { 
		if(language.empty()) {
		std::cout << "language empty "<<std::endl;
			return "";
		}
		return *std::find(m_languages().begin(), m_languages().end(), language); 
	}

	const std::string getCurrentLanguage() { return m_currentLanguage; }
	static const std::vector<std::string> GetAllLanguages() { return m_languages(); }
private:
	std::string m_currentLanguage;
	boost::locale::generator m_gen;
	static const std::vector<std::string> m_languages() { 
		return {"en", "nl", "de", "ast", "da", "es", "fa", "fi", "fr", "hu", "it", "ja", "pl","pt","sv", "zh"};
	}
};