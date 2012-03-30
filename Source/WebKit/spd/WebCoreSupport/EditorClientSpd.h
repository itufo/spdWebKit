#ifndef EditorClientSpd_h
#define EditorClientSpd_h

#include "EditorClient.h"
#include "TextCheckerClient.h"

class WebView;

namespace WebKit {

class EditorClientSpd : public WebCore::EditorClient, public WebCore::TextCheckerClient {
public:
    EditorClientSpd(WebView*);
    ~EditorClientSpd();

    virtual void pageDestroyed();

    virtual bool shouldDeleteRange(WebCore::Range*);
    virtual bool shouldShowDeleteInterface(WebCore::HTMLElement*);
    virtual bool smartInsertDeleteEnabled();
    virtual bool isSelectTrailingWhitespaceEnabled();
    virtual bool isContinuousSpellCheckingEnabled();
    virtual void toggleContinuousSpellChecking();
    virtual bool isGrammarCheckingEnabled();
    virtual void toggleGrammarChecking();
    virtual int spellCheckerDocumentTag();

    virtual bool shouldBeginEditing(WebCore::Range*);
    virtual bool shouldEndEditing(WebCore::Range*);
    virtual bool shouldInsertNode(WebCore::Node*, WebCore::Range*, WebCore::EditorInsertAction);
    virtual bool shouldInsertText(const WTF::String&, WebCore::Range*, WebCore::EditorInsertAction);
    virtual bool shouldChangeSelectedRange(WebCore::Range*, WebCore::Range*, WebCore::EAffinity, bool);

    virtual bool shouldApplyStyle(WebCore::CSSStyleDeclaration*, WebCore::Range*);
    virtual bool shouldMoveRangeAfterDelete(WebCore::Range*, WebCore::Range*);

    virtual void didBeginEditing();
    virtual void respondToChangedContents();
    virtual void respondToChangedSelection(WebCore::Frame*);
    virtual void didEndEditing();
    virtual void didWriteSelectionToPasteboard();
    virtual void didSetSelectionTypesForPasteboard();

    virtual void registerUndoStep(WTF::PassRefPtr<WebCore::UndoStep>);
    virtual void registerRedoStep(WTF::PassRefPtr<WebCore::UndoStep>);
    virtual void clearUndoRedoOperations();

    virtual bool canCopyCut(WebCore::Frame*, bool defaultValue) const;
    virtual bool canPaste(WebCore::Frame*, bool defaultValue) const;
    virtual bool canUndo() const;
    virtual bool canRedo() const;

    virtual void undo();
    virtual void redo();

    virtual const char* interpretKeyEvent(const WebCore::KeyboardEvent*);
    virtual bool handleEditingKeyboardEvent(WebCore::KeyboardEvent*);
    virtual void handleKeyboardEvent(WebCore::KeyboardEvent*);
    virtual void handleInputMethodKeydown(WebCore::KeyboardEvent*);

    virtual void textFieldDidBeginEditing(WebCore::Element*);
    virtual void textFieldDidEndEditing(WebCore::Element*);
    virtual void textDidChangeInTextField(WebCore::Element*);
    virtual bool doTextFieldCommandFromEvent(WebCore::Element*, WebCore::KeyboardEvent*);
    virtual void textWillBeDeletedInTextField(WebCore::Element*);
    virtual void textDidChangeInTextArea(WebCore::Element*);

    virtual void ignoreWordInSpellDocument(const WTF::String&);
    virtual void learnWord(const WTF::String&);
    virtual void checkSpellingOfString(const UChar*, int, int*, int*);
    virtual WTF::String getAutoCorrectSuggestionForMisspelledWord(const WTF::String&);
    virtual void checkGrammarOfString(const UChar*, int, WTF::Vector<WebCore::GrammarDetail>&, int*, int*);
    virtual void updateSpellingUIWithGrammarString(const WTF::String&, const WebCore::GrammarDetail&);
    virtual void updateSpellingUIWithMisspelledWord(const WTF::String&);
    virtual void showSpellingUI(bool);
    virtual bool spellingUIIsShowing();
    virtual void getGuessesForWord(const WTF::String& word, const WTF::String& context, WTF::Vector<WTF::String>& guesses);
    virtual void willSetInputMethodState();
    virtual void setInputMethodState(bool);
    virtual void requestCheckingOfString(WebCore::SpellChecker*, int, WebCore::TextCheckingTypeMask, const WTF::String&) {}
    virtual WebCore::TextCheckerClient* textChecker() { return this; }

private:
    WebView* m_webView;
};

} // namespace WebKit

#endif // EditorClientSpd_h
