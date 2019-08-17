#ifndef MASKWIDGET_H
#define MASKWIDGET_H
#include <QWidget>

class CMaskWidget : public QWidget
{
public:
	static CMaskWidget* GetInstance();
	static void UnInstance();
	//! 设置被遮盖的控件
	void SetMainWidget(QWidget *pWidgetMasked);
	/*
	* \brief: 设置触发遮盖动作的控件名字
	*
	* \param[in]: lstWidgetNames 控件名字数组
	*/
	void SetDialogNames(const QStringList &lstWidgetNames);
	/*
	* \brief: 设置透明度
	*
	* \param[in]: fOpacity 透明度 取值范围0-1 1: 完全透明; 0: 完全不透明
	*/
	void SetOpacity(float fOpacity);
protected:
	virtual void paintEvent(QPaintEvent *event) override;
	virtual void showEvent(QShowEvent* event) override;
	virtual bool eventFilter(QObject *obj, QEvent *event) override;
private:
	explicit CMaskWidget(QWidget* wgt = nullptr);
	~CMaskWidget();
private:
	static CMaskWidget* m_pMask;
	QWidget* m_pDlgToBeMasked = nullptr;
	QStringList m_lstNamesForDlgPrompt;
};
#endif // MASKWIDGET_H