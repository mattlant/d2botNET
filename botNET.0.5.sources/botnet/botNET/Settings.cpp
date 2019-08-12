#include "botnet.h"
#include "settings.h"
#include "game.h"
#include "configuration.h"

namespace botNET
{

	void Settings::DirectoryCreator(DirectoryInfo* path)
	{
		if(!path->Exists)
			path->Create();
	}

	DirectoryInfo* Settings::GetDirectoryInfo(Config* cfg, String* root, String* node)
	{
		String* xmlPath = String::Concat("Directories/", node);
		return new DirectoryInfo(String::Concat(root, S"\\", cfg->GetValue(xmlPath, node)));
	}

	String* Settings::GetAutoLoaded()[]
	{
		XmlDocument* doc = Settings::gGlobalConfig->mDocument;
		XmlNode* nodeAutoLoad = doc->DocumentElement->SelectSingleNode("//AssemblyLoading"); 

		XmlNodeList* assNodes = nodeAutoLoad->ChildNodes;

		ArrayList* temp = new ArrayList();

		IEnumerator* eNode = assNodes->GetEnumerator();

		int i = 0;
		while(eNode->MoveNext())
		{
			XmlNode* node = __try_cast<XmlNode*>(eNode->Current);
			if(node->LocalName->Equals("Load"))
				temp->Add(node->InnerText->Trim()); 
		}


		String* loads __gc[] = new String*[temp->Count];
		temp->CopyTo(loads);
		return loads;
	}

}