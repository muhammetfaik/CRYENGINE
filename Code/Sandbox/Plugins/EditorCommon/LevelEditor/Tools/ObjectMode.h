// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.
#pragma once

// CryCommon
#include "CryExtension/CryGUID.h"
#include <CrySerialization/yasli/decorators/Range.h>

// EditorInterface
#include "IObjectManager.h"

// EditorCommon
#include "EditorFramework/Preferences.h"
#include "Gizmos/ITransformManipulator.h"

// {87109FED-BDB5-4874-936D-338400079F58}
DEFINE_GUID(OBJECT_MODE_GUID, 0x87109fed, 0xbdb5, 0x4874, 0x93, 0x6d, 0x33, 0x84, 0x0, 0x7, 0x9f, 0x58);

struct EDITOR_COMMON_API SDeepSelectionPreferences : public SPreferencePage
{
	SDeepSelectionPreferences()
		: SPreferencePage("Deep Selection", "General/General")
		, deepSelectionRange(1.0f)
	{
	}

	virtual bool Serialize(yasli::Archive& ar) override
	{
		ar.openBlock("deepSelection", "Deep Selection");
		ar(yasli::Range(deepSelectionRange, 0.0f, 1000.0f), "deepSelectionRange", "Range");
		ar.closeBlock();

		return true;
	}

	float deepSelectionRange;
};

EDITOR_COMMON_API extern SDeepSelectionPreferences gDeepSelectionPreferences;

class CBaseObject;
class CDeepSelection;
class CObjectMode;

class CObjectManipulatorOwner final : public ITransformManipulatorOwner
{
public:
	CObjectManipulatorOwner(CObjectMode* objectModeTool);
	~CObjectManipulatorOwner();

	bool GetManipulatorMatrix(Matrix34& tm) override;
	void GetManipulatorPosition(Vec3& position) override;
	bool IsManipulatorVisible() override;

	void OnObjectChanged(const CBaseObject* pObject, const CObjectEvent& event);
	void OnObjectsChanged(const std::vector<CBaseObject*>& objects, const CObjectEvent& event);
	void OnSelectionChanged(const std::vector<CBaseObject*>& selected, const std::vector<CBaseObject*>& deselected);

private:
	void UpdateVisibilityState();

	bool                   m_visibilityDirty;
	bool                   m_bIsVisible;
	ITransformManipulator* m_manipulator;
};

/*!
 *	CObjectMode is an abstract base class for All Editing Tools supported by Editor.
 *	Edit tools handle specific editing modes in viewports.
 */
class EDITOR_COMMON_API CObjectMode : public CEditTool
{
public:

	struct EDITOR_COMMON_API ISubTool
	{
		virtual ~ISubTool() {}
		virtual bool HandleMouseEvent(CViewport* view, EMouseEvent event, CPoint& point, int flags) = 0;
	};

	DECLARE_DYNCREATE(CObjectMode);

	CObjectMode();
	virtual ~CObjectMode();

	void Activate() override;

	//////////////////////////////////////////////////////////////////////////
	// CEditTool implementation.
	//////////////////////////////////////////////////////////////////////////
	virtual string GetDisplayName() const override { return "Select Objects"; }
	virtual void   Display(SDisplayContext& dc);
	virtual void   DisplaySelectionPreview(SDisplayContext& dc);

	virtual bool   MouseCallback(CViewport* view, EMouseEvent event, CPoint& point, int flags);
	virtual bool   OnKeyDown(CViewport* view, uint32 nChar, uint32 nRepCnt, uint32 nFlags);
	virtual bool   OnKeyUp(CViewport* view, uint32 nChar, uint32 nRepCnt, uint32 nFlags);

	virtual bool   IsDisplayGrid() override;

	void           OnManipulatorBeginDrag(IDisplayViewport* view, ITransformManipulator* pManipulator, const Vec2i& point, int flags);
	void           OnManipulatorDrag(IDisplayViewport* view, ITransformManipulator* pManipulator, const Vec2i& p0, const Vec3& value, int flags);
	void           OnManipulatorEndDrag(IDisplayViewport* view, ITransformManipulator* pManipulator);

	void           RegisterSubTool(ISubTool* pSubTool);
	void           UnRegisterSubTool(ISubTool* pSubTool);

public:
	enum ECommandMode
	{
		NothingMode = 0,
		ScrollZoomMode,
		SelectMode,
		MoveMode,
		RotateMode,
		ScaleMode,
		ScrollMode,
		ZoomMode,
	};
	void         SetCommandMode(ECommandMode mode)      { m_commandMode = mode; }
	ECommandMode GetCommandMode() const                 { return m_commandMode; }
	Vec3&        GetScale(const CViewport* view, const CPoint& point, Vec3& OutScale);
	void         SetTransformChanged(bool bTransformed) { m_bTransformChanged = bTransformed; }

protected:
	bool OnLButtonDown(CViewport* view, int nFlags, CPoint point);
	bool OnLButtonDblClk(CViewport* view, int nFlags, CPoint point);
	bool OnLButtonUp(CViewport* view, int nFlags, CPoint point);
	bool OnRButtonDown(CViewport* view, int nFlags, CPoint point);
	bool OnRButtonUp(CViewport* view, int nFlags, CPoint point);
	bool OnMButtonDown(CViewport* view, int nFlags, CPoint point);
	bool OnMouseMove(CViewport* view, int nFlags, CPoint point);

	bool CheckVirtualKey(int virtualKey);

	//! Ctrl-Click in move mode to move selected objects to given pos.
	void         MoveSelectionToPos(CViewport* view, Vec3& pos, bool align, const CPoint& point);
	void         SetObjectCursor(CViewport* view, CBaseObject* hitObj, IObjectManager::ESelectOp selectMode);

	virtual void DeleteThis() { delete this; }

	void         AwakeObjectAtPoint(CViewport* view, CPoint point);

	void         HideMoveByFaceNormGizmo();
	void         HandleMoveByFaceNormal(HitContext& hitInfo);
	void         UpdateMoveByFaceNormGizmo(CBaseObject* pHitObject);
	void         AllowHighlightChange() { m_suspendHighlightChange = false; }

private:
	class NormalGizmoOwner : public ITransformManipulatorOwner
	{
		virtual void GetManipulatorPosition(Vec3& position) {}
	};

	void CheckDeepSelection(HitContext& hitContext, CViewport* pWnd);

	CPoint       m_cMouseDownPos;
	Vec3         m_mouseDownWorldPos;
	CPoint       m_rMouseDownPos;
	bool         m_bDragThresholdExceeded;
	ECommandMode m_commandMode;

	CryGUID      m_MouseOverObject;
	bool         m_openContext;
	// used to keep highlight from disappearing when we use right click menu
	bool         m_suspendHighlightChange;

	typedef std::vector<CryGUID> TGuidContainer;
	std::unordered_set<ISubTool*> m_subTools;
	TGuidContainer                m_PreviewGUIDs;

	_smart_ptr<CDeepSelection>    m_pDeepSelection;

	bool                          m_bMoveByFaceNormManipShown;
	CBaseObject*                  m_pHitObject;

	bool                          m_bTransformChanged;

	ITransformManipulator*        m_normalMoveGizmo;
	NormalGizmoOwner              m_normalGizmoOwner;
	CObjectManipulatorOwner       m_objectManipulatorOwner;

	bool                          m_bGizmoDrag;
};

typedef CAutoRegister<CObjectMode::ISubTool> CAutoRegisterObjectModeSubToolHelper;

#define REGISTER_OBJECT_MODE_SUB_TOOL_PTR(Type, typePtr)                                                            \
  namespace Internal                                                                                                \
  {                                                                                                                 \
  void RegisterObjectModeSubTool ## Type()                                                                          \
  {                                                                                                                 \
    CEditTool* pTool = GetIEditorImpl()->GetLevelEditorSharedState()->GetEditTool();                                \
    if (!pTool || !pTool->IsKindOf(RUNTIME_CLASS(CObjectMode)))                                                     \
      return;                                                                                                       \
    CObjectMode* pObjectMode = static_cast<CObjectMode*>(pTool);                                                    \
    pObjectMode->RegisterSubTool(typePtr);                                                                          \
  }                                                                                                                 \
  CAutoRegisterObjectModeSubToolHelper g_AutoRegObjectModeSubToolHelper ## Type(RegisterObjectModeSubTool ## Type); \
  }
