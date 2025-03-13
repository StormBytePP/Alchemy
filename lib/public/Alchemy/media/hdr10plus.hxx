#pragma once

#include <Alchemy/visibility.h>

/**
 * @namespace Alchemist
 * @brief The main namespace for the Alchemist library.
 */
namespace Alchemist {
	struct ALCHEMY_PUBLIC HDR10Plus {
		/**
		 * @brief Gets HDR10+ version
		 * @return Version string
		 */
		static std::string 										Version();
	};
}