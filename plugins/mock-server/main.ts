import express from 'express'
import fs from 'fs'
import ResponseBuilder from './responseBuilder'


const options = JSON.parse(fs.readFileSync('./settings.json').toString())

const app = express()
app.use('/', (req: express.Request, res: express.Response) => {
    const rb = new ResponseBuilder(options, req)
    rb.end(res)
})

app.listen(80, () => {
    console.log('Server start!')
})




