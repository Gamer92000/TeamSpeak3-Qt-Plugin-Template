#include "config.h"
#include "ui_config.h"

config::config(const QString& configLocation, QWidget* parent /* = nullptr */) : QDialog(parent),
	m_ui(std::make_unique<Ui::configui>()),
	m_settings(std::make_unique<QSettings>(configLocation, QSettings::IniFormat, this))
{
	m_ui->setupUi(this);

	setWindowTitle("Qt Example Plugin :: Config");

	// Connect UI Elements.
	connect(m_ui->pbOk, &QPushButton::clicked, this, &config::saveSettings);
	connect(m_ui->pbCancel, &QPushButton::clicked, this, &QWidget::close);

	adjustSize();
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

config::~config() {
	m_settings->sync();
}


void config::setConfigOption(const QString& option, const QVariant& value) {
	m_settings->setValue(option, value);
}

QVariant config::getConfigOption(const QString& option) const {
	return m_settings->value(option);
}

void config::showEvent(QShowEvent* /* e */) {
	adjustSize();
	loadSettings();
}

void config::changeEvent(QEvent* e) {
	if (e->type() == QEvent::StyleChange && isVisible()) {
		m_ui->verticalLayoutWidget_2->adjustSize();
		adjustSize();
	}
}

void config::saveSettings() {
	setConfigOption("exampleSwitch", m_ui->exampleSwitch->isChecked());
	setConfigOption("exampleText", m_ui->exampleText->text());
	setConfigOption("exampleNumber", m_ui->exampleNumber->value());

	close();
}

void config::loadSettings() {
	m_ui->exampleSwitch->setChecked(getConfigOption("exampleSwitch").toBool());
	m_ui->exampleText->setText(getConfigOption("exampleText").toString());
	m_ui->exampleNumber->setValue(getConfigOption("exampleNumber").toInt());
}