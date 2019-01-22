#include "common/IDebugLog.h"  // IDebugLog
#include "fose/GameAPI.h"  // g_dataHandler
#include "fose/GameData.h"  // DataHandler
#include "fose/GameForms.h"  // TESTopicInfo
#include "fose/PluginAPI.h"  // OBSEMessagingInterface
#include "fose_common/fose_version.h"  // FALLOUT_VERSION

#include <ShlObj.h>  // CSIDL_MYDOCUMENTS

#include "RE/TESTopic.h"  // TESTopic
#include "RE/TESTopicInfo.h"  // TESTopicInfo


static PluginHandle					g_pluginHandle = kPluginHandle_Invalid;
static FOSESerializationInterface*	g_serialization = 0;


void SerializationHandler(void*)
{
	DataHandler* dataHandler = *g_dataHandler;
	RE::TESTopic* topic = 0;
	RE::TESTopicInfo* topicInfo = 0;
	for (auto it = dataHandler->topicList.Begin(); !it.End(); ++it) {
		topic = (RE::TESTopic*)*it;
		_MESSAGE("DIAL: %08X", topic->refID);
		if (topic->questInfoData) {
			for (UInt32 i = 0; i < topic->questInfoData->infoList.m_size; ++i) {
				topicInfo = topic->questInfoData->infoList.m_data[i];
				_MESSAGE("INFO: %08X", topicInfo->refID);
			}
		}
	}
}


extern "C" {
	bool FOSEPlugin_Query(const FOSEInterface* a_fose, PluginInfo* a_info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Fallout3\\FOSE\\INFODumpFO.log");
		gLog.SetPrintLevel(IDebugLog::kLevel_DebugMessage);
		gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage);

		a_info->infoVersion = PluginInfo::kInfoVersion;
		a_info->name = "INFODumpFO";
		a_info->version = 1;

		g_pluginHandle = a_fose->GetPluginHandle();

		if (a_fose->isEditor) {
			_FATALERROR("[FATAL ERROR] Loaded in editor, marking as incompatible!\n");
			return false;
		}

		if (a_fose->runtimeVersion != FALLOUT_VERSION_1_7) {
			_FATALERROR("[FATAL ERROR] Unsupported runtime version %08X!\n", a_fose->runtimeVersion);
			return false;
		}

		return true;
	}

	bool FOSEPlugin_Load(const FOSEInterface* a_fose)
	{
		g_serialization = (FOSESerializationInterface*)a_fose->QueryInterface(kInterface_Serialization);
		g_serialization->SetNewGameCallback(g_pluginHandle, SerializationHandler);
		return true;
	};
}
