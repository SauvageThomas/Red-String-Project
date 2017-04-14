package model.tools;

import org.xml.sax.Attributes;
import org.xml.sax.helpers.DefaultHandler;

import model.entities.Article;

public class SAXHandler extends DefaultHandler {

	private String currentTag;
	private Article article;
	private String content;

	public SAXHandler() {
		this.article = new Article();
		this.content = new String();
	}

	@Override
	public void startDocument() {
		System.out.println("startDocument");
	}

	@Override
	public void startElement(String uri, String localName, String qName, Attributes attributes) {
		this.currentTag = qName;
		System.out.println(qName);
	}

	@Override
	public void characters(char[] caracteres, int debut, int longueur) {
		String content = new String(caracteres, debut, longueur);
		System.out.println(content);
		switch (this.currentTag) {
		case "auteur":
			this.article.setAuthor(content);
			break;
		case "date":
			this.article.setDate(content);
			break;
		case "titre":
			this.article.setTitle(content);
			break;
		case "resume":
			System.out.println("Résumé !"+content);
			this.article.setSummary(content);
			break;
		case "phrase":
			this.content += content + "\n";
			this.article.setContent(this.content);
			break;
		default:
			System.out.println("Tag not used " + this.currentTag);
			break;
		}
	}

	@Override
	public void endElement(String uri, String localName, String qName) {
		this.currentTag = new String();
		System.out.println("Fin tag " + qName);
	}

	@Override
	public void endDocument() {
		System.out.println("endDocument");
		System.out.println(this.article);
	}
	
	public Article retrieveArticle(){
		return this.article;
	}
}
