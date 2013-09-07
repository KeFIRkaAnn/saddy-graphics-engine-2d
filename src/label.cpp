#include "label.h"
#include "renderer.h"

DECLARE_SOBJ_INHERITANCE(Label,sad::BasicNode)
DECLARE_SOBJ_INHERITANCE(FormattedLabel,Label)

void Label::operator()(const sad::ResizeEvent & o)
{
	float old_width=(float)(m_renderer->settings().width());
	float old_height=(float)(m_renderer->settings().height());
	m_rend_point.setX(m_p.x() * o.new_width/old_width);
	m_rend_point.setY(m_p.y() * o.new_height/old_height);
}
Label::Label(sad::Renderer * renderer)
{
	m_renderer = renderer;
	m_renderer->controls()->addResizeHandler(this,false);
}
Label::Label(
		      LabelFont fnt,
		      const hst::string & str,
			  const pointf      & p,
			  sad::Renderer * renderer
			)
{
	m_renderer = renderer;
    m_fnt=fnt;
	m_str=str;
	m_p=p;
	m_rend_point=p;
	m_renderer->controls()->addResizeHandler(this,false);
}

Label::~Label()
{
	m_renderer->controls()->removeResizeHandler(this);
}

void Label::render()
{
	m_fnt->render(m_str,m_rend_point);
}

FormattedLabel::Arg::~Arg()
{

}

FormattedLabel::FormattedLabel(sad::Renderer * renderer) : Label(renderer)
{
	m_created = true;
	m_timer.start();
}

void FormattedLabel::setFont(const hst::string & fnt, sad::Renderer * r)
{
	sad::BasicFont * font = r->fonts()->get(fnt);
	if (font)
		setFont(font);
}


void FormattedLabel::update()
{
	fmt::TempFormatter<> stream = fmt::Format(m_format_string);
	for(unsigned int i = 0; i < m_args.size(); i++)
	{
		m_args[i]->substitute(stream);
	}
	this->string() = str(stream);
}

void FormattedLabel::render()
{
	m_timer.stop();
	if (m_created || m_timer.elapsed() >= m_update_interval)	
	{
		m_timer.start();
		m_created = false;
		this->update();
	}
	this->Label::render();
}

FormattedLabel::~FormattedLabel()
{
	for(unsigned int i = 0; i < m_args.size(); i++)
	{
		delete m_args[i];
	}
}


FormattedLabel * FormattedLabel::argFPS(sad::Renderer * r)
{
	return this->arg(r, &sad::Renderer::fps);
}
