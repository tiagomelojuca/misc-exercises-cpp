#ifndef PERSONA_GEN_H_
#define PERSONA_GEN_H_

#include <iosfwd>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

namespace PersonaSVG
{
  namespace Utils {
    typedef unsigned char BYTE;

    // Snippets from René Nyffenegger / LihO 
    // https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c
    // https://renenyffenegger.ch/notes/development/Base64/Encoding-and-decoding-base-64-with-cpp/
    static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    static inline bool is_base64(BYTE c) { return (isalnum(c) || (c == '+') || (c == '/')); }
    std::string base64_encode(BYTE const* buf, unsigned int bufLen)
    {
      std::string ret;
      int i = 0;
      int j = 0;
      BYTE char_array_3[3];
      BYTE char_array_4[4];

      while (bufLen--) {
        char_array_3[i++] = *(buf++);
        if (i == 3) {
          char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
          char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
          char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
          char_array_4[3] = char_array_3[2] & 0x3f;

          for(i = 0; (i <4) ; i++)
            ret += base64_chars[char_array_4[i]];
          i = 0;
        }
      }

      if (i)
      {
        for(j = i; j < 3; j++)
          char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
          ret += base64_chars[char_array_4[j]];

        while((i++ < 3))
          ret += '=';
      }

      return ret;
    }
    std::vector<BYTE> base64_decode(std::string const& encoded_string)
    {
      int in_len = encoded_string.size();
      int i = 0;
      int j = 0;
      int in_ = 0;
      BYTE char_array_4[4], char_array_3[3];
      std::vector<BYTE> ret;

      while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i ==4) {
          for (i = 0; i <4; i++)
            char_array_4[i] = base64_chars.find(char_array_4[i]);

          char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
          char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
          char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

          for (i = 0; (i < 3); i++)
              ret.push_back(char_array_3[i]);
          i = 0;
        }
      }

      if (i) {
        for (j = i; j <4; j++)
          char_array_4[j] = 0;

        for (j = 0; j <4; j++)
          char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++) ret.push_back(char_array_3[j]);
      }

      return ret;
    }
  }

  enum class PlaceholdersFields
  { NOME_PERSONA, PAPEL, IDADE, GENERO, CLASSE_SOCIAL, ESCOLARIDADE, RENDA, LIFE_BODY, FOTO };

  struct PlaceholdersData
  {
    std::string NOME_PERSONA  = "${NOME_PERSONA}";
    std::string PAPEL         = "${PAPEL}";
    std::string IDADE         = "${IDADE}";
    std::string GENERO        = "${GENERO}";
    std::string CLASSE_SOCIAL = "${CLASSE_SOCIAL}";
    std::string ESCOLARIDADE  = "${ESCOLARIDADE}";
    std::string RENDA         = "${RENDA}";
    std::string LIFE_BODY     = "${LIFE_BODY}";
    std::string FOTO          = "${FOTO}";

    std::string Get(PlaceholdersFields field) const
    {
      switch (field) {
        case PlaceholdersFields::NOME_PERSONA  : return NOME_PERSONA;
        case PlaceholdersFields::PAPEL         : return PAPEL;
        case PlaceholdersFields::IDADE         : return IDADE;
        case PlaceholdersFields::GENERO        : return GENERO;
        case PlaceholdersFields::CLASSE_SOCIAL : return CLASSE_SOCIAL;
        case PlaceholdersFields::ESCOLARIDADE  : return ESCOLARIDADE;
        case PlaceholdersFields::RENDA         : return RENDA;
        case PlaceholdersFields::LIFE_BODY     : return LIFE_BODY;
        case PlaceholdersFields::FOTO          : return FOTO;
      }

      return "";
    }
  };

  static constexpr const char* content = R""""(<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<!-- Created with Inkscape (http://www.inkscape.org/) -->

<svg
   width="210mm"
   height="297mm"
   viewBox="0 0 210 297"
   version="1.1"
   id="svg5"
   inkscape:version="1.2 (dc2aedaf03, 2022-05-15)"
   sodipodi:docname="persona_tmpl.svg"
   xml:space="preserve"
   xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape"
   xmlns:sodipodi="http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd"
   xmlns:xlink="http://www.w3.org/1999/xlink"
   xmlns="http://www.w3.org/2000/svg"
   xmlns:svg="http://www.w3.org/2000/svg"><sodipodi:namedview
     id="namedview7"
     pagecolor="#ffffff"
     bordercolor="#000000"
     borderopacity="0.25"
     inkscape:showpageshadow="2"
     inkscape:pageopacity="0.0"
     inkscape:pagecheckerboard="0"
     inkscape:deskcolor="#d1d1d1"
     inkscape:document-units="mm"
     showgrid="false"
     showguides="true"
     inkscape:zoom="1"
     inkscape:cx="280"
     inkscape:cy="258.5"
     inkscape:window-width="1920"
     inkscape:window-height="991"
     inkscape:window-x="-9"
     inkscape:window-y="-9"
     inkscape:window-maximized="1"
     inkscape:current-layer="layer1" /><defs
     id="defs2"><pattern
       inkscape:collect="always"
       xlink:href="#pattern7387"
       id="pattern8171"
       patternTransform="matrix(0.2648305,0,0,0.26595747,25,20.000001)" /><linearGradient
       id="linearGradient956"
       inkscape:swatch="solid"><stop
         style="stop-color:#999999;stop-opacity:1;"
         offset="0"
         id="stop954" /></linearGradient><rect
       x="95.5"
       y="414"
       width="620"
       height="640"
       id="rect4939" /><pattern
       patternUnits="userSpaceOnUse"
       width="113.28"
       height="150.39999"
       patternTransform="translate(236.35999,-123.19999)"
       id="pattern7387"><image
         width="113.28"
         height="150.39999"
         preserveAspectRatio="none"
         xlink:href="${FOTO}"
         id="image6294"
         x="0"
         y="0" /></pattern><clipPath
       clipPathUnits="userSpaceOnUse"
       id="clipPath8173"><rect
         style="fill:#999999;fill-opacity:1;stroke-width:0.201742"
         id="rect8175"
         width="30.000002"
         height="40"
         x="25"
         y="20"
         rx="1"
         ry="1" /></clipPath></defs><g
     inkscape:groupmode="layer"
     id="layer3"
     inkscape:label="Body"
     sodipodi:insensitive="true"><text
       xml:space="preserve"
       id="text4937"
       style="font-style:normal;font-variant:normal;font-weight:bold;font-stretch:normal;font-size:13.3333px;font-family:sans-serif;-inkscape-font-specification:'sans-serif Bold';white-space:pre;shape-inside:url(#rect4939);display:inline;fill:#1a1a1a;fill-opacity:1"
       transform="matrix(0.26458333,0,0,0.26458333,-0.32838576,-5.0697514)"
       x="0"
       y="0"><tspan
         x="95.5"
         y="426.13164"
         id="tspan8257"><tspan
           style="font-weight:normal;-inkscape-font-specification:sans-serif;text-align:justify"
           id="tspan8255">${LIFE_BODY}</tspan></tspan></text></g><g
     inkscape:groupmode="layer"
     id="layer2"
     inkscape:label="Resume"
     sodipodi:insensitive="true"><rect
       style="fill:#000000;fill-opacity:0.5;stroke-width:0.128141"
       id="rect3429"
       width="170"
       height="0.5"
       x="20"
       y="65"
       rx="0.5"
       ry="0.25" /><rect
       style="fill:#000000;fill-opacity:0.5;stroke-width:0.128141"
       id="rect3429-5"
       width="170"
       height="0.5"
       x="20"
       y="100"
       rx="0.5"
       ry="0.25" /><text
       xml:space="preserve"
       style="font-style:italic;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:4.23333px;font-family:sans-serif;-inkscape-font-specification:'sans-serif Italic';fill:#000000;fill-opacity:0.5;stroke-width:0.264583"
       x="24.864534"
       y="73.746498"
       id="text4052"><tspan
         sodipodi:role="line"
         id="tspan4050"
         style="font-size:4.23333px;fill:#1a1a1a;fill-opacity:1;stroke-width:0.264583"
         x="24.864534"
         y="73.746498"><tspan
   style="font-style:normal;font-variant:normal;font-weight:bold;font-stretch:normal;font-family:sans-serif;-inkscape-font-specification:'sans-serif Bold'"
   id="tspan4796">Idade              :</tspan> <tspan
   style="font-size:1.41111px"
   id="tspan4810"> </tspan>${IDADE}</tspan><tspan
         sodipodi:role="line"
         style="font-size:4.23333px;fill:#1a1a1a;fill-opacity:1;stroke-width:0.264583"
         x="24.864534"
         y="79.038162"
         id="tspan4104"><tspan
   style="font-style:normal;font-variant:normal;font-weight:bold;font-stretch:normal;font-family:sans-serif;-inkscape-font-specification:'sans-serif Bold'"
   id="tspan4798">Gênero           :</tspan> <tspan
   style="font-size:1.41111px"
   id="tspan4806"> </tspan>${GENERO}</tspan><tspan
         sodipodi:role="line"
         style="font-size:4.23333px;fill:#1a1a1a;fill-opacity:1;stroke-width:0.264583"
         x="24.864534"
         y="84.329819"
         id="tspan4106"><tspan
   style="font-style:normal;font-variant:normal;font-weight:bold;font-stretch:normal;font-family:sans-serif;-inkscape-font-specification:'sans-serif Bold'"
   id="tspan4800">Classe Social :</tspan> ${CLASSE_SOCIAL}</tspan><tspan
         sodipodi:role="line"
         style="font-size:4.23333px;fill:#1a1a1a;fill-opacity:1;stroke-width:0.264583"
         x="24.864534"
         y="89.621483"
         id="tspan4108"><tspan
   style="font-style:normal;font-variant:normal;font-weight:bold;font-stretch:normal;font-family:sans-serif;-inkscape-font-specification:'sans-serif Bold'"
   id="tspan4802">Escolaridade :</tspan> ${ESCOLARIDADE}</tspan><tspan
         sodipodi:role="line"
         style="font-size:4.23333px;fill:#1a1a1a;fill-opacity:1;stroke-width:0.264583"
         x="24.864534"
         y="94.913147"
         id="tspan4110"><tspan
   style="font-style:normal;font-variant:normal;font-weight:bold;font-stretch:normal;font-family:sans-serif;-inkscape-font-specification:'sans-serif Bold'"
   id="tspan4804">Renda             :</tspan> ${RENDA}</tspan></text></g><g
     inkscape:label="Header"
     inkscape:groupmode="layer"
     id="layer1"
     sodipodi:insensitive="true"><rect
       style="fill:url(#pattern8171);stroke:none;stroke-width:0.265393"
       width="30"
       height="40"
       x="25"
       y="20"
       id="rect7390"
       clip-path="url(#clipPath8173)" /><text
       xml:space="preserve"
       style="font-size:6.34998px;fill:#999999;fill-opacity:1;stroke-width:0.264582"
       x="64.428665"
       y="34.825985"
       id="text3285"><tspan
         sodipodi:role="line"
         id="tspan3283"
         style="font-style:normal;font-variant:normal;font-weight:bold;font-stretch:normal;font-size:6.34998px;font-family:sans-serif;-inkscape-font-specification:'sans-serif Bold';fill:#000000;stroke-width:0.264582"
         x="64.428665"
         y="34.825985">${NOME_PERSONA}</tspan></text><text
       xml:space="preserve"
       style="font-size:5.64447px;fill:#999999;fill-opacity:1;stroke-width:0.264584"
       x="64.768219"
       y="44.32375"
       id="text3285-1"><tspan
         sodipodi:role="line"
         id="tspan3283-9"
         style="font-style:italic;font-variant:normal;font-weight:normal;font-stretch:normal;font-size:5.64447px;font-family:sans-serif;-inkscape-font-specification:'sans-serif Italic';fill:#000000;stroke-width:0.264584"
         x="64.768219"
         y="44.32375">${PAPEL}</tspan></text></g></svg>
)"""";

  void FillField(
    std::string& svg,
    const PlaceholdersData& defaultPlaceholders,
    const PlaceholdersData& data,
    const PlaceholdersFields& field
  )
  {
    svg.replace(
      svg.find(defaultPlaceholders.Get(field)),
      defaultPlaceholders.Get(field).length(),
      data.Get(field)
    );
  }

  void FillFields(
    std::string& svg,
    const PlaceholdersData& data
  )
  {
    PlaceholdersData defaultPlaceholders;

    FillField(svg, defaultPlaceholders, data, PlaceholdersFields::NOME_PERSONA);
    FillField(svg, defaultPlaceholders, data, PlaceholdersFields::PAPEL);
    FillField(svg, defaultPlaceholders, data, PlaceholdersFields::IDADE);
    FillField(svg, defaultPlaceholders, data, PlaceholdersFields::GENERO);
    FillField(svg, defaultPlaceholders, data, PlaceholdersFields::CLASSE_SOCIAL);
    FillField(svg, defaultPlaceholders, data, PlaceholdersFields::ESCOLARIDADE);
    FillField(svg, defaultPlaceholders, data, PlaceholdersFields::RENDA);
    FillField(svg, defaultPlaceholders, data, PlaceholdersFields::LIFE_BODY);
    FillField(svg, defaultPlaceholders, data, PlaceholdersFields::FOTO);
  }

  std::string SVG(const PlaceholdersData& data)
  {
    std::string svg = content;
    FillFields(svg, data);

    return svg;
  }

  std::string SVG(const std::string jsonPath)
  {
    std::ifstream f(jsonPath);
    nlohmann::json json = nlohmann::json::parse(f);
    f.close();

    PersonaSVG::PlaceholdersData data;
    data.NOME_PERSONA  = json["nomePersona"];
    data.PAPEL         = json["papelNaExperiencia"];
    data.IDADE         = json["idade"];
    data.GENERO        = json["genero"];
    data.CLASSE_SOCIAL = json["classeSocial"];
    data.ESCOLARIDADE  = json["escolaridade"];
    data.RENDA         = json["renda"];
    data.LIFE_BODY     = json["historia"];
    data.FOTO          = json["caminhoFoto"];

    std::filesystem::path photoPath = std::filesystem::u8path(data.FOTO.c_str());
    std::ifstream photo(photoPath, std::ios::binary);
    if (photo.is_open()) {
      photo.seekg(0, std::ios::end);
      const int sSize = photo.tellg();
      photo.seekg(0, std::ios::beg);

      auto buffer = new Utils::BYTE[sSize];
      photo.read(reinterpret_cast<char*>(buffer), sSize);
      data.FOTO = "data:image;base64," + Utils::base64_encode(buffer, sSize);

      delete[] buffer;
      photo.close();
    }

    return SVG(data);
  }
}

#endif
