﻿/***********************************************************************************
**
** UOFileReader.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/

#ifndef MULREADER_H
#define MULREADER_H

//!Класс для чтения данных из файлов и создания текстур
class UOFileReader
{
public:
    UOFileReader() {}
    ~UOFileReader() {}

    /*!
	Получить массив пикселей гампа
	@param [__in] io Ссылка на данные о гампе
	@return Массив пикселей или nullptr
	*/
    USHORT_LIST GetGumpPixels(CIndexObject &io);

    /*!
	Прочитать гамп и сгенерировать текстуру
	@param [__in] io Ссылка на данные о гампе
	@return Ссылка на данные о текстуре
	*/
    CGLTexture *ReadGump(CIndexObject &io);

    USHORT_LIST GetArtPixels(ushort id, CIndexObject &io, bool run, short &width, short &height);

    /*!
	Прочитать арт и сгенерировать текстуру
	@param [__in] ID Индекс арта
	@param [__in] io Ссылка на данные о арте
	@return Ссылка на данные о текстуре
	*/
    CGLTexture *ReadArt(ushort id, CIndexObject &io, bool run);

    /*!
	Прочитать текстуру ландшафта и сгенерировать тексруту
	@param [__in] io Ссылка на данные о текстуре ландшафта
	@return Ссылка на данные о текстуре
	*/
    CGLTexture *ReadTexture(CIndexObject &io);

    /*!
	Прочитать освещение и сгенерировать текстуру
	@param [__in] io Ссылка на данные о освещении
	@return Ссылка на данные о текстуре
	*/
    CGLTexture *ReadLight(CIndexObject &io);
};

//!Класс чтения данных
extern UOFileReader g_UOFileReader;

#endif
