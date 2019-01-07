#pragma once

#include "fs.hh"
#include "configuration.hh"

#include <boost/locale.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

#define _(x) boost::locale::translate(x).str()
#define translate_noop(x) x

class TranslationEngine {
public:
	TranslationEngine(const char *package) {
		boost::locale::generator gen;
		gen.add_messages_path(getLocaleDir().string());
		gen.add_messages_domain(package);
		try {
			std::locale::global(gen(boost::locale::util::get_system_locale(true)));
			//auto locale = gen("");
			//std::cout << "locale generated" << std::endl;
			//std::locale::global(locale);
			//std::cout << "Global locale set" << std::endl;
			//std::cout << "Current global locale is " << locale.name();
		} catch (...) {
			std::clog << "locale/warning: Unable to detect locale, will try to fallback to en_US.UTF-8" << std::endl;
			std::locale::global(gen("en_US.UTF-8"));
		}
		// boost::locale::generator gen;	
		// gen.add_messages_path(getLocaleDir().string());
		// gen.add_messages_domain(package);

		m_package = package;
		// auto languageFromConfig = config["game/language"].getEnumName();
		// std::cout << "language from config is: '" << languageFromConfig << "'" << std::endl;
		// if(languageFromConfig.empty()) {
		// 	setLanguage("");
		// } else {
		// 	setLanguage(languageFromConfig);
		// }
	};
	static bool enabled() {
		return true;
	};

	void setLanguage(const std::string language) { 
		boost::locale::generator gen;	
		gen.add_messages_path(getLocaleDir().string());
		gen.add_messages_domain(m_package);

		std::cout << "languag: '"<<language<<"'"<<std::endl;
		m_currentLanguage = getLanguage(language);
		std::cout << "found languag: '"<<m_currentLanguage<<"'"<<std::endl;

		try {
			//std::locale::global(m_gen(m_currentLanguage));
			std::locale::global(gen("nl_NL.UTF-8"));
			std::cout << "language setted correctly to: '"<< m_currentLanguage <<"'" << std::endl;
		} catch (...) {
			std::clog << "locale/warning: Unable to detect locale, will try to fallback to en_US.UTF-8" << std::endl;
			std::locale::global(gen("en_US.UTF-8"));	
		}
	}

	const std::string getLanguage(const std::string language) { 
		if(language.empty()) {
			auto lan = boost::locale::util::get_system_locale(true);
			std::cout << "No given language.. using default system language: '" << lan << "''" << std::endl;
			return lan;
		}
		return *std::find(GetAllLanguages().begin(), GetAllLanguages().end(), language); 
	}

	const std::string getCurrentLanguage() { return m_currentLanguage; }
	std::vector<std::string> GetAllLanguages() { return config["game/language"].getAllEnumStringValues(); }
private:
	std::string m_currentLanguage;
	const char *m_package;
};
