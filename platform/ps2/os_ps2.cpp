/**************************************************************************/
/*  os_ps2.cpp                                                            */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "os_ps2.h"

#include "main/main.h"

void OS_PS2::set_main_loop(MainLoop *p_main_loop) {
    main_loop = p_main_loop;
}

void OS_PS2::delete_main_loop() {
	if (main_loop) {
		memdelete(main_loop);
		main_loop = nullptr;
	}
}

bool _check_internal_feature_support(const String &p_feature) {
    // PS2_TODO: Check for features
    return true;
}

String OS_PS2::get_name() const {
    return "PS2";
}

MainLoop *OS_PS2::get_main_loop() const {
    return main_loop;
}

void OS_PS2::initialize() {}

void OS_PS2::initialize_joypads() {}

void OS_PS2::run() {
	if (!main_loop) {
		return;
	}

	main_loop->initialize();

	while (true) {
		if (Main::iteration()) {
			break;
		}
	}

	main_loop->finalize();
}

void OS_PS2::finalize() {
    finalize_core();
}

OS_PS2::OS_PS2() {}
