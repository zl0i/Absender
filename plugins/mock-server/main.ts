import express from 'express'
import fs from 'fs'
import ResponseBuilder from './responseBuilder'


var options = JSON.parse(fs.readFileSync('./settings.json').toString())

fs.watchFile('./settings.json', { interval: 1000 }, (_curr, _prev) => {
    options = JSON.parse(fs.readFileSync('./settings.json').toString())
})

const app = express()
app.use('/', (req: express.Request, res: express.Response) => {
    const rb = new ResponseBuilder(options.hosts, req)
    rb.end(res)
})

app.listen(80, () => {
    console.log('Server start!')
})




