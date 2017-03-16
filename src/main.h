#pragma once

#define PLUGIN_NAME "Output Switcher"
#define PLUGIN_VERSION "1.0"


class OutputSwitcher : private ui_extension::container_ui_extension
{
	private:
	struct ComboboxItem
	{
		pfc::string8 name;
		GUID guid;
		bool selected;

		bool operator== (const ComboboxItem &other) const
		{
			return ((this->selected == other.selected) && (this->guid == other.guid) && (this->name == other.name));
		}

		bool operator!= (const ComboboxItem &other) const
		{
			return !(*this == other);
		}
	};

	typedef pfc::list_t<ComboboxItem> ItemList;


	public:
	// ui_extension::extension_base
	const GUID & get_extension_guid() const override
	{
		static const GUID guid = {0x23d9ea6, 0x7e8c, 0x4a45, {0x8e, 0x6, 0xcb, 0x58, 0x76, 0x73, 0xe9, 0x4a}};
		return guid;
	}

	void get_name(pfc::string_base & out) const override
	{
		out = PLUGIN_NAME;
	}


	// ui_extension::window
	void get_category(pfc::string_base & out) const override
	{
		out = "Toolbars";
	}

	bool get_description(pfc::string_base & out) const override
	{
		out = "An dropdown combo box to change output device quickly";
		return true;
	};

	unsigned get_type() const override
	{
		return ui_extension::window_type_t::type_toolbar;
	};


	// ui_helpers::container_window
	class_data & get_class_data()const override
	{
		static const TCHAR className[] = _T("{B7A22167 - 25FC - 4B8B - 901C - C428A5EDB109}");
		__implement_get_class_data(className, false);
	}

	LRESULT on_message(HWND wnd, UINT msg, WPARAM wp, LPARAM lp) override;


	private:
	void initCombobox();
	void clearCombobox() const;
	bool addToCombobox(const char *str) const;

	bool selectItem(const int idx) const;
	bool getSelectItem(ComboboxItem &out) const;

	bool setComboboxWidth(const int width) const;

	ItemList menuFindCommands() const;
	static void menuExecCommand(const GUID &commandGuid);

	ItemList m_comboboxEntries = {};

	HWND m_combobox = NULL;
	HWND m_toolTip = NULL;
	HFONT m_uiHfont = NULL;

	LONG m_HEIGHT = 0;
	int m_minSizeWidth = INT_MAX;
	int m_fullSizeWidth = 0;
};
static ui_extension::window_factory<OutputSwitcher> output_switcher_impl;
