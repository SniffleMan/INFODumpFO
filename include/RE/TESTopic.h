#pragma once

#include "fose/GameForms.h"  // TESForm, TESFullName, TESQuest

#include "RE/TopicInfoArray.h"  // TopicInfoArray


namespace RE
{
	class TESTopic :
		public TESForm,		// 00
		public TESFullName	// 18
	{
	public:
		struct QuestInfoData
		{
			TESQuest*		parentQuest;
			TopicInfoArray	infoList;
		};


		virtual ~TESTopic();	// 00


		// members
		UInt32			unk24;			// 24
		UInt32			unk28;			// 28
		QuestInfoData*	questInfoData;	// 2C
		UInt32			unk30;			// 30
		UInt32			unk34;			// 34
		UInt32			unk38;			// 38
		UInt32			unk3C;			// 3C
	};
}
