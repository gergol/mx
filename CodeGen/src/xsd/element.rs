use crate::error::Result;
use crate::xsd::annotation::Annotation;
use crate::xsd::annotation::Item::Documentation;
use crate::xsd::complex_type::ComplexType;
use crate::xsd::constants::{ANNOTATION, COMPLEX_TYPE, ELEMENT, TYPE};
use crate::xsd::{name_attribute, type_attribute, EntryType, Occurs, ID};
use std::convert::TryInto;

/*
annotation
complexType
 */

/* attributes...
[block final name]
[name type]
[maxOccurs minOccurs name type]
 */

pub enum Element {
    Definition(ElementDef),
    Reference(ElementRef),
}

impl Element {
    pub fn documentation(&self) -> String {
        match self {
            Element::Definition(x) => {
                if let Some(annotation) = &x.annotation {
                    return annotation.documentation();
                }
            }
            Element::Reference(x) => {
                if let Some(annotation) = &x.annotation {
                    return annotation.documentation();
                }
            }
        }
        return "".to_owned();
    }

    pub fn id(&self) -> &ID {
        match self {
            Element::Definition(x) => &x.id,
            Element::Reference(x) => &x.id,
        }
    }

    pub fn from_xml(node: &exile::Element, index: u64) -> Result<Element> {
        if let Some(_) = node.attributes.map().get(TYPE) {
            Ok(Element::Reference(ElementRef::from_xml(node, index)?))
        } else {
            Ok(Element::Definition(ElementDef::from_xml(node, index)?))
        }
    }
}

pub struct ElementDef {
    pub id: ID,
    pub index: u64,
    pub annotation: Option<Annotation>,
    pub name: String,
    pub occurs: Occurs,
    pub complex_type: ComplexType,
}

impl ElementDef {
    pub fn documentation(&self) -> String {
        if let Some(annotation) = &self.annotation {
            return annotation.documentation();
        }
        return "".to_owned();
    }

    pub fn from_xml(node: &exile::Element, index: u64) -> Result<Self> {
        if node.name.as_str() != ELEMENT {
            return raise!("expected '{}', got '{}'", ELEMENT, node.name.as_str());
        }
        let mut annotation = None;
        let mut complex_type = None;
        for inner in node.children() {
            let t = inner.name.as_str();
            match t {
                ANNOTATION => annotation = Some(Annotation::from_xml(inner, index)?),
                COMPLEX_TYPE => complex_type = Some(ComplexType::from_xml(inner, index)?),
                _ => return raise!("unsupported inner type: '{}'", t),
            }
        }
        let complex_type = if let Some(x) = complex_type {
            x
        } else {
            return raise!("{} not found!", COMPLEX_TYPE);
        };
        let name = name_attribute(node)?;
        let id = ID {
            entry_type: EntryType::Element,
            name: name.clone(),
        };
        Ok(ElementDef {
            id,
            index,
            annotation,
            name,
            occurs: Occurs::from_xml(node)?,
            complex_type,
        })
    }
}

pub struct ElementRef {
    pub id: ID,
    pub index: u64,
    pub annotation: Option<Annotation>,
    pub name: String,
    pub type_: String,
    pub occurs: Occurs,
}

impl ElementRef {
    pub fn documentation(&self) -> String {
        if let Some(annotation) = &self.annotation {
            return annotation.documentation();
        }
        return "".to_owned();
    }

    pub fn from_xml(node: &exile::Element, index: u64) -> Result<Self> {
        if node.name.as_str() != ELEMENT {
            return raise!("expected '{}', got '{}'", ELEMENT, node.name.as_str());
        }
        let mut annotation = None;
        for inner in node.children() {
            let t = inner.name.as_str();
            if t == ANNOTATION {
                annotation = Some(Annotation::from_xml(inner, index)?);
                break;
            }
        }
        let name = name_attribute(node)?;
        let id = ID {
            entry_type: EntryType::Element,
            name: name.clone(),
        };
        Ok(ElementRef {
            id,
            index,
            annotation,
            name,
            type_: type_attribute(node)?,
            occurs: Occurs::from_xml(node)?,
        })
    }
}

// #[test]
// fn parse_score_partwise() {
//     let xml_str = r#"
//     	<xs:element name="score-partwise" block="extension substitution" final="\#all">
// 		<xs:annotation>
// 			<xs:documentation>bleep bleep bloop bloop</xs:documentation>
// 		</xs:annotation>
// 		<xs:complexType>
// 			<xs:sequence>
// 				<xs:group ref="score-header"/>
// 				<xs:element name="part" maxOccurs="unbounded">
// 					<xs:complexType>
// 						<xs:sequence>
// 							<xs:element name="measure" maxOccurs="unbounded">
// 								<xs:complexType>
// 									<xs:group ref="music-data"/>
// 									<xs:attributeGroup ref="measure-attributes"/>
// 								</xs:complexType>
// 							</xs:element>
// 						</xs:sequence>
// 						<xs:attributeGroup ref="part-attributes"/>
// 					</xs:complexType>
// 				</xs:element>
// 			</xs:sequence>
// 			<xs:attributeGroup ref="document-attributes"/>
// 		</xs:complexType>
// 	</xs:element>"#;
//     let doc = exile::parse(xml_str).unwrap();
//     let xml = doc.root();
//     let want_index: u64 = 3;
//     let ele = Element::from_xml(&xml, want_index).unwrap();
//     let got_id = format!("{}", ele.id());
//     let want_id = "score-partwise (element)";
//     assert_eq!(got_id.as_str(), want_id);
//     let got_doc = ele.documentation();
//     let want_doc = "bleep bleep bloop bloop";
//     assert_eq!(got_doc, want_doc);
//     let ele = match ele {
//         Element::Definition(x) => x,
//         Element::Reference(_) => panic!("expected Definition, got Reference"),
//     };
//     assert_eq!(
//         ele.occurs,
//         Occurs {
//             min_occurs: 1,
//             max_occurs: Some(1),
//         }
//     );
//     match ele.complex_type {
//         ComplexType::Inline(_) => {}
//         ComplexType::Named(_) => panic!("expected ComplexType::Inline, got ComplexType::Named"),
//     }
// }

#[test]
fn parse_credit() {
    let xml_str =
        r#"<xs:element name="credit" type="credit" minOccurs="0" maxOccurs="unbounded"/>"#;
    let doc = exile::parse(xml_str).unwrap();
    let xml = doc.root();
    let want_index: u64 = 6;
    let ele = Element::from_xml(&xml, want_index).unwrap();
    let got_id = format!("{}", ele.id());
    let want_id = "credit (element)";
    assert_eq!(got_id.as_str(), want_id);
    let got_doc = ele.documentation();
    let want_doc = "";
    assert_eq!(got_doc, want_doc);
    let ele = match ele {
        Element::Definition(_) => panic!("expected Reference, got Definition"),
        Element::Reference(x) => x,
    };
    assert_eq!(ele.name.as_str(), "credit");
    assert_eq!(ele.type_.as_str(), "credit");
    assert_eq!(
        ele.occurs,
        Occurs {
            min_occurs: 0,
            max_occurs: None,
        }
    );
}