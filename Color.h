/**
 * @file Color.h
 * @brief ANSI color codes for formatted console output.
 *
 * This header defines common ANSI escape codes for coloring
 * terminal output. These values can be prepended to console
 * output streams to modify text color, and reset afterward
 * using Color::RESET.
 *
 * Example usage:
 * @code
 * std::cout << Color::RED << "Error!" << Color::RESET << std::endl;
 * @endcode
 */

#pragma once
#include <string>

/**
 * @namespace Color
 * @brief Contains ANSI escape codes for colored terminal output.
 *
 * These constants represent standard ANSI color sequences.
 * They work in terminals that support ANSI escape codes
 * (Linux, macOS, most modern Windows terminals).
 */
namespace Color {

    /** 
     * @brief Resets text formatting to default.
     */
    static const std::string RESET  = "\033[0m";

    /** 
     * @brief Red text color.
     */
    static const std::string RED    = "\033[31m";

    /** 
     * @brief Green text color.
     */
    static const std::string GREEN  = "\033[32m";

    /** 
     * @brief Yellow text color.
     */
    static const std::string YELLOW = "\033[33m";

    /** 
     * @brief Blue text color.
     */
    static const std::string BLUE   = "\033[34m";

    /** 
     * @brief Magenta text color.
     */
    static const std::string MAGENTA= "\033[35m";

    /** 
     * @brief Cyan text color.
     */
    static const std::string CYAN   = "\033[36m";

    /** 
     * @brief White text color.
     */
    static const std::string WHITE  = "\033[37m";

    /** 
     * @brief Bright turquoise (light cyan) text color.
     */
    static const std::string TURQUOISE = "\033[96m";
}