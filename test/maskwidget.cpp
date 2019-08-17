#include "maskwidget.h"
#include <QMutex>
#include <QEvent>
#include <QPainter>
#include <QApplication>

CMaskWidget* CMaskWidget::m_pMask = nullptr;

CMaskWidget* CMaskWidget::GetInstance()
{
	static QMutex s_Mutex;
	if (nullptr == m_pMask)
	{
		QMutexLocker locker(&s_Mutex);
		if (nullptr == m_pMask)
		{
			m_pMask = new CMaskWidget;
			m_pMask->setAttribute(Qt::WA_DeleteOnClose);
		}
	}
	return m_pMask;
}

void CMaskWidget::UnInstance()
{
	static QMutex s_Mutex;
	if (nullptr != m_pMask)
	{
		QMutexLocker locker(&s_Mutex);
		if (nullptr != m_pMask)
		{
			delete m_pMask;
			m_pMask = nullptr;
		}
	}
}
void CMaskWidget::SetMainWidget(QWidget *pWidgetMasked)
{
	if (m_pDlgToBeMasked != pWidgetMasked)
	{
		m_pDlgToBeMasked = pWidgetMasked;
		setGeometry(m_pDlgToBeMasked->geometry());
	}
}

void CMaskWidget::SetDialogNames(const QStringList &lstWidgetNames)
{
	if (m_lstNamesForDlgPrompt != lstWidgetNames)
	{
		m_lstNamesForDlgPrompt = lstWidgetNames;
	}
}

void CMaskWidget::SetOpacity(float fOpacity)
{
	setWindowOpacity(fOpacity);
}

void CMaskWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QPoint start_point(0, 0);
	QPoint end_point(0, this->height());

	//QLinearGradient进行渐变色设置
	QLinearGradient gradient(start_point, end_point);
	gradient.setColorAt(0.7, QColor(255, 255, 255, 0));
	gradient.setColorAt(0.8, QColor(250, 250, 250, 100));
	gradient.setColorAt(0.9, QColor(245, 245, 245, 150));
	gradient.setColorAt(1, QColor(240, 240, 240, 200));
	QRect rect(0, 0, width(), height());
	painter.fillRect(rect, QBrush(gradient));
	painter.setPen(Qt::transparent);
	painter.drawRect(rect);
	painter.end();
}

void CMaskWidget::showEvent(QShowEvent* event)
{
	if (nullptr != m_pDlgToBeMasked)
	{
		//! 获取被遮盖的窗口的宽高
		QRect rectDlgMasked = m_pDlgToBeMasked->geometry();
		int nWidth = rectDlgMasked.width();
		int nHeight = rectDlgMasked.height();
		setGeometry(0, 0, nWidth, nHeight);
	}
	QWidget::showEvent(event);
}

bool CMaskWidget::eventFilter(QObject *obj, QEvent *event)
{
	if (QEvent::Show == event->type())
	{
		if (m_lstNamesForDlgPrompt.contains(obj->objectName()))
		{
			this->setVisible(true);
		}
	}
	else if (QEvent::Hide == event->type())
	{
		if (m_lstNamesForDlgPrompt.contains(obj->objectName()))
		{
			this->setVisible(false);
		}
	}
	return QWidget::eventFilter(obj, event);
}

CMaskWidget::CMaskWidget(QWidget* wgt /* = nullptr */)
{
	setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground, true);
	setAttribute(Qt::WA_TransparentForMouseEvents, true);
	//setStyleSheet("border:0px;");
}

CMaskWidget::~CMaskWidget()
{
	m_lstNamesForDlgPrompt.clear();
}