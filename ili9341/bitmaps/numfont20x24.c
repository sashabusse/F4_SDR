/*
 * Copyright (c) 2014-2015, TAKAHASHI Tomohiro (TTRFTECH) edy555@gmail.com
 * All rights reserved.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * The software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include <stdint.h>

const uint32_t numfont20x24[][24] = {
		{	// 0
		0b00000111111111000000100000000000,
		0b00011111111111110000000000000000,
		0b00111111111111111000000000000000,
		0b01111111111111111100000000000000,
		0b01111110000011111100000000000000,
		0b11111100000001111110000000000000,
		0b11111000000000111110000000000000,
		0b11111000000000111110000000000000,

		0b11111000000000111110000000000000,
		0b11111000000000111110000000000000,
		0b11111000000000111110000000000000,
		0b11111000000000111110000000000000,
		0b11111000000000111110000000000000,
		0b11111000000000111110000000000000,
		0b11111000000000111110000000000000,
		0b11111000000000111110000000000000,

		0b11111100000001111110000000000000,
		0b01111110000011111100000000000000,
		0b01111111111111111100000000000000,
		0b00111111111111111000000000000000,
		0b00011111111111110000000000000000,
		0b00000111111111000000100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// 1
		0b00000000011111000000100000000000,
		0b00000000111111000000000000000000,
		0b00000000111111000000000000000000,
		0b00000001111111000000000000000000,
		0b00000111111111000000000000000000,
		0b00011111111111000000000000000000,
		0b00011111111111000000000000000000,
		0b00011111111111000000000000000000,

		0b00011111011111000000000000000000,
		0b00011111011111000000000000000000,
		0b00000000011111000000000000000000,
		0b00000000011111000000000000000000,
		0b00000000011111000000000000000000,
		0b00000000011111000000000000000000,
		0b00000000011111000000000000000000,
		0b00000000011111000000000000000000,

		0b00000000011111000000000000000000,
		0b00000000011111000000000000000000,
		0b00000000011111000000000000000000,
		0b00000000011111000000000000000000,
		0b00000000011111000000000000000000,
		0b00000000011111000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// 2
		0b00000011111110000000100000000000,
		0b00001111111111100000000000000000,
		0b00111111111111111000000000000000,
		0b01111111111111111100000000000000,
		0b01111110000011111100000000000000,
		0b11111100000001111110000000000000,
		0b11111000000000111110000000000000,
		0b11111000000001111110000000000000,

		0b00000000000011111110000000000000,
		0b00000000001111111100000000000000,
		0b00000000111111111000000000000000,
		0b00000011111111100000000000000000,
		0b00001111111110000000000000000000,
		0b00011111111000000000000000000000,
		0b00111111100000000000000000000000,
		0b01111111000000000000000000000000,

		0b11111110000000000000000000000000,
		0b11111100000000000000000000000000,
		0b11111111111111111110000000000000,
		0b11111111111111111110000000000000,
		0b11111111111111111110000000000000,
		0b11111111111111111110000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// 3
		0b00000011111110000000100000000000,
		0b00001111111111100000000000000000,
		0b00111111111111111000000000000000,
		0b01111111111111111100000000000000,
		0b01111110000011111100000000000000,
		0b11111100000001111110000000000000,
		0b11111000000000111110000000000000,
		0b11111000000001111110000000000000,

		0b00000000000011111100000000000000,
		0b00000000111111111100000000000000,
		0b00000000111111110000000000000000,
		0b00000000111111110000000000000000,
		0b00000000111111111000000000000000,
		0b00000000000011111100000000000000,
		0b11111000000000111110000000000000,
		0b11111000000000111110000000000000,

		0b11111000000000111110000000000000,
		0b11111110000001111110000000000000,
		0b01111111111111111100000000000000,
		0b00111111111111111000000000000000,
		0b00001111111111110000000000000000,
		0b00000001111110000000100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// 4
		0b00000000000011110000100000000000,
		0b00000000000111110000000000000000,
		0b00000000001111110000000000000000,
		0b00000000011111110000000000000000,
		0b00000000111111110000000000000000,
		0b00000001111111110000000000000000,
		0b00000011111111110000000000000000,
		0b00000111111111110000000000000000,

		0b00001111110111110000000000000000,
		0b00011111100111110000000000000000,
		0b00111111000111110000000000000000,
		0b01111110000111110000000000000000,
		0b11111100000111110000000000000000,
		0b11111000000111110000000000000000,
		0b11111111111111111110000000000000,
		0b11111111111111111110000000000000,

		0b11111111111111111110000000000000,
		0b11111111111111111110000000000000,
		0b00000000000111110000000000000000,
		0b00000000000111110000000000000000,
		0b00000000000111110000000000000000,
		0b00000000000111110000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// 5
		0b11111111111111111110100000000000,
		0b11111111111111111110000000000000,
		0b11111111111111111110000000000000,
		0b11111111111111111110000000000000,
		0b11110000000000000000000000000000,
		0b11110000000000000000000000000000,
		0b11110000000000000000000000000000,
		0b11110011111110000000000000000000,

		0b11111111111111110000000000000000,
		0b11111111111111111000000000000000,
		0b11111111111111111100000000000000,
		0b11111110000011111100000000000000,
		0b00000000000001111110000000000000,
		0b00000000000000111110000000000000,
		0b00000000000000111110000000000000,
		0b11111000000000111110000000000000,

		0b11111000000001111110000000000000,
		0b11111110000111111110000000000000,
		0b01111111111111111100000000000000,
		0b00111111111111111000000000000000,
		0b00001111111111110000000000000000,
		0b00000001111110000000100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// 6
		0b00000011111111100000100000000000,
		0b00011111111111111000000000000000,
		0b00111111111111111100000000000000,
		0b01111111111111111100000000000000,
		0b01111110000001111100000000000000,
		0b11111100000000000000000000000000,
		0b11111000000000000000000000000000,
		0b11111000000000000000000000000000,

		0b11111011111110000000000000000000,
		0b11111111111111110000000000000000,
		0b11111111111111111000000000000000,
		0b11111111111111111100000000000000,
		0b11111110000111111100000000000000,
		0b11111100000001111110000000000000,
		0b11111000000000111110000000000000,
		0b11111000000000111110000000000000,

		0b11111100000001111110000000000000,
		0b11111110000011111110000000000000,
		0b01111111111111111100000000000000,
		0b00111111111111111000000000000000,
		0b00001111111111110000000000000000,
		0b00000001111110000000100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// 7
		0b11111111111111111110100000000000,
		0b11111111111111111110000000000000,
		0b11111111111111111110000000000000,
		0b11111111111111111110000000000000,
		0b00000000000001111110000000000000,
		0b00000000000011111100000000000000,
		0b00000000000111111000000000000000,
		0b00000000001111110000000000000000,

		0b00000000011111100000000000000000,
		0b00000000011111000000000000000000,
		0b00000000111111000000000000000000,
		0b00000000111110000000000000000000,
		0b00000001111110000000000000000000,
		0b00000001111100000000000000000000,
		0b00000001111100000000000000000000,
		0b00000011111100000000000000000000,

		0b00000011111000000000000000000000,
		0b00000011111000000000000000000000,
		0b00000011111000000000000000000000,
		0b00000011111000000000000000000000,
		0b00000011111000000000000000000000,
		0b00000011111000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// 8
		0b00000011111110000000100000000000,
		0b00001111111111100000000000000000,
		0b00111111111111111000000000000000,
		0b01111111111111111100000000000000,
		0b01111110000011111100000000000000,
		0b11111100000001111110000000000000,
		0b11111000000000111110000000000000,
		0b01111100000001111100000000000000,

		0b01111110000011111100000000000000,
		0b00111111111111111000000000000000,
		0b00011111111111110000000000000000,
		0b00011111111111110000000000000000,
		0b00111111111111111000000000000000,
		0b01111110000011111100000000000000,
		0b11111100000001111110000000000000,
		0b11111000000000111110000000000000,

		0b11111000000000111110000000000000,
		0b11111100000001111110000000000000,
		0b01111111111111111100000000000000,
		0b00111111111111111000000000000000,
		0b00011111111111110000000000000000,
		0b00000111111111000000100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// 9
		0b00000011111110000000100000000000,
		0b00001111111111100000000000000000,
		0b00111111111111111000000000000000,
		0b01111111111111111100000000000000,
		0b01111110000011111100000000000000,
		0b11111100000001111110000000000000,
		0b11111000000000111110000000000000,
		0b11111000000000111110000000000000,

		0b11111100000000111110000000000000,
		0b11111110000001111110000000000000,
		0b01111111111111111110000000000000,
		0b00111111111111111110000000000000,
		0b00001111111111111110000000000000,
		0b00000011111111111110000000000000,
		0b00000000000000111110000000000000,
		0b00000000000000111110000000000000,

		0b11111000000001111110000000000000,
		0b11111100000011111100000000000000,
		0b11111111111111111100000000000000,
		0b01111111111111111000000000000000,
		0b00111111111111110000000000000000,
		0b00001111111111000000100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// . (period) = \001 10
		0b00000000000000000000100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,

		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,

		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000001110000000000000000000000,
		0b00000011111000000000000000000000,
		0b00000011111000000000000000000000,
		0b00000001110000000000100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// - (minus) = \002 11
		0b00000000000000000000100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,

		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00111111111111111100000000000000,
		0b00111111111111111100000000000000,
		0b00111111111111111100000000000000,
		0b00111111111111111100000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,

		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// infinity = \003 12
		0b00000000000000000000100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000111100011110000000000000000,
		0b00001111110111111000000000000000,
		0b00011111110111111100000000000000,

		0b00111000111100011100000000000000,
		0b01111000111000011110000000000000,
		0b01110000011000001110000000000000,
		0b01110000011000001110000000000000,
		0b01110000011000001110000000000000,
		0b01110000011000001110000000000000,
		0b01111000011100011110000000000000,
		0b00111000111100011100000000000000,

		0b00111111101111111100000000000000,
		0b00011111101111111000000000000000,
		0b00001111000111100000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// dB = \004 13
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000011101111110000000000000000,

		0b00000011101111110000000000000000,
		0b00000011101111111100000000000000,
		0b00000011101110011110000000000000,
		0b00000011101110001110000000000000,
		0b00111111101110011110000000000000,
		0b01111111101111111100000000000000,
		0b11111111101111111000000000000000,
		0b11110011101111111100000000000000,

		0b11100011101110011110000000000000,
		0b11100011101110001110000000000000,
		0b11110011101110011110000000000000,
		0b01111111101111111110000000000000,
		0b01111111101111111100000000000000,
		0b00111101101111110000100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// speaker = \005 14
		0b00000000000000000000000000000000,
		0b00000000000000111000000000000000,
		0b00000000000001111000000000000000,
		0b00000000000011011000000000000000,
		0b00000000000110011000000000000000,
		0b00000000001100011000000000000000,
		0b00011111111000011000000000000000,
		0b00011111110000011000000000000000,

		0b00011000110000011000000000000000,
		0b00011000110000011000000000000000,
		0b00011000110000011000000000000000,
		0b00011000110000011000000000000000,
		0b00011000110000011000000000000000,
		0b00011000110000011000000000000000,
		0b00011111110000011000000000000000,
		0b00011111111000011000000000000000,

		0b00000000001100011000000000000000,
		0b00000000000110011000000000000000,
		0b00000000000011011000000000000000,
		0b00000000000001111000000000000000,
		0b00000000000000111000000000000000,
		0b00000000000000000000100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// antenna = \006 15
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00111111111111111100000000000000,
		0b00111111111111111100000000000000,

		0b00110000011000001100000000000000,
		0b00011000011000011000000000000000,
		0b00001100011000110000000000000000,
		0b00000110011001100000000000000000,
		0b00000011011011000000000000000000,
		0b00000001111110000000000000000000,
		0b00000000111100000000000000000000,
		0b00000000011000000000000000000000,

		0b00000000011000000000000000000000,
		0b00000000011000000000000000000000,
		0b00000000011000000000000000000000,
		0b00000000011000000000000000000000,
		0b00000000011000000000000000000000,
		0b00000000011000000000100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// x1 = \007 16
		0b00000000000000000000100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000011110000000000000,
		0b00000000000000111110000000000000,
		0b00000000000001111110000000000000,

		0b00000000000011111110000000000000,
		0b00000000000011111110000000000000,
		0b00000000000000111110000000000000,
		0b00000000000000111110000000000000,
		0b00110000011000111110000000000000,
		0b11111000111100111110000000000000,
		0b01111101111000111110000000000000,
		0b00011111110000111110000000000000,

		0b00001111100000111110000000000000,
		0b00001111100000111110000000000000,
		0b00011111110000111110000000000000,
		0b00111101111000111110000000000000,
		0b01111000111100111110000000000000,
		0b00110000011000111110100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// k = \010 17
		0b01111100000000000000100000000000,
		0b01111100000000000000000000000000,
		0b01111100000000000000000000000000,
		0b01111100000000000000000000000000,
		0b01111100000000000000000000000000,
		0b01111100000000000000000000000000,
		0b01111100000111111000000000000000,
		0b01111100001111110000000000000000,

		0b01111100011111100000000000000000,
		0b01111100111111000000000000000000,
		0b01111101111110000000000000000000,
		0b01111111111100000000000000000000,
		0b01111111111000000000000000000000,
		0b01111111110000000000000000000000,
		0b01111111110000000000000000000000,
		0b01111111111000000000000000000000,

		0b01111111111100000000000000000000,
		0b01111101111110000000000000000000,
		0b01111100111111000000000000000000,
		0b01111100011111100000000000000000,
		0b01111100001111110000000000000000,
		0b01111100000111111000100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// M = \011 18
		0b11111000000000111110100000000000,
		0b11111000000000111110000000000000,
		0b11111100000001111110000000000000,
		0b11111100000001111110000000000000,
		0b11111110000011111110000000000000,
		0b11111110000011111110000000000000,
		0b11111111000111111110000000000000,
		0b11111111000111111110000000000000,

		0b11111111101111111110000000000000,
		0b11111111101111111110000000000000,
		0b11111111111111111110000000000000,
		0b11111111111111111110000000000000,
		0b11111111111111111110000000000000,
		0b11111111111111111110000000000000,
		0b11111011111110111110000000000000,
		0b11111011111110111110000000000000,

		0b11111001111100111110000000000000,
		0b11111001111100111110000000000000,
		0b11111000111000111110000000000000,
		0b11111000111000111110000000000000,
		0b11111000000000111110000000000000,
		0b11111000000000111110100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// G = \012 19
		0b00000111111111000000100000000000,
		0b00011111111111110000000000000000,
		0b00111111111111111000000000000000,
		0b01111111111111111100000000000000,
		0b01111110000011111100000000000000,
		0b11111100000001111110000000000000,
		0b11111000000000111110000000000000,
		0b11111000000000111110000000000000,

		0b11111000000000000000000000000000,
		0b11111000000000000000000000000000,
		0b11111000000000000000000000000000,
		0b11111000000000000000000000000000,
		0b11111000000111111110000000000000,
		0b11111000000111111110000000000000,
		0b11111000000111111110000000000000,
		0b11111000000111111110000000000000,

		0b11111100000001111110000000000000,
		0b01111110000011111110000000000000,
		0b01111111111111111110000000000000,
		0b00111111111111111110000000000000,
		0b00011111111111111110000000000000,
		0b00000111111110111110100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// BS = \013 20
		0b00000000000000000000100000000000,
		0b00000000001000000000000000000000,
		0b00000000011000000000000000000000,
		0b00000000111000000000000000000000,
		0b00000001111000000000000000000000,
		0b00000011111000000000000000000000,
		0b00000111111111111110000000000000,
		0b00001111111111111110000000000000,

		0b00011111111111111110000000000000,
		0b00111111111111111110000000000000,
		0b01111111111111111110000000000000,
		0b11111111111111111110000000000000,
		0b01111111111111111110000000000000,
		0b00111111111111111110000000000000,
		0b00011111111111111110000000000000,
		0b00001111111111111110000000000000,

		0b00000111111111111110000000000000,
		0b00000011111000000000000000000000,
		0b00000001111000000000000000000000,
		0b00000000111000000000000000000000,
		0b00000000011000000000000000000000,
		0b00000000001000000000100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		},
		{	// m = \014 21
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,

		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b11111011100000000000000000000000,
		0b11111111110000000000000000000000,
		0b11111111111000000000000000000000,
		0b11101110111000000000000000000000,

		0b11101110111000000000000000000000,
		0b11101110111000000000000000000000,
		0b11101110111000000000000000000000,
		0b11101110111000000000000000000000,
		0b11101110111000000000000000000000,
		0b11101110111000000000100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// dB = \015 22
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000001110000000000000,

		0b00000000000000001110000000000000,
		0b00000000000000001110000000000000,
		0b00000000000000001110000000000000,
		0b00000000000000001110000000000000,
		0b00000000000011111110000000000000,
		0b00000000000111111110000000000000,
		0b00000000001111111110000000000000,
		0b00000000001111001110000000000000,

		0b00000000001110001110000000000000,
		0b00000000001110001110000000000000,
		0b00000000001111001110000000000000,
		0b00000000000111111110000000000000,
		0b00000000000111111110000000000000,
		0b00000000000011110110100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
		{	// m = \016 23
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000,
		0b11111100000000000000000000000000,
                    
		0b11111111000000000000000000000000,
		0b11111111100000000000000000000000,
		0b11100111100000000000000000000000,
		0b11100011100000000000000000000000,
		0b11100111101101101100000000000000,
		0b11111111001111111110000000000000,
		0b11111110001111111111000000000000,
		0b11111111001110110111000000000000,
                    
		0b11100111101110110111000000000000,
		0b11100011101110110111000000000000,
		0b11100111101110110111000000000000,
		0b11111111101110110111000000000000,
		0b11111111001110110111000000000000,
		0b11111100001110110111100000000000,
		0b00000000000000000000000000000000,
		0b00000000000000000000000000000000
		},
};
