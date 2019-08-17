#ifndef MASKWIDGET_H
#define MASKWIDGET_H
#include <QWidget>

class CMaskWidget : public QWidget
{
public:
	static CMaskWidget* GetInstance();
	static void UnInstance();
	//! ���ñ��ڸǵĿؼ�
	void SetMainWidget(QWidget *pWidgetMasked);
	/*
	* \brief: ���ô����ڸǶ����Ŀؼ�����
	*
	* \param[in]: lstWidgetNames �ؼ���������
	*/
	void SetDialogNames(const QStringList &lstWidgetNames);
	/*
	* \brief: ����͸����
	*
	* \param[in]: fOpacity ͸���� ȡֵ��Χ0-1 1: ��ȫ͸��; 0: ��ȫ��͸��
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